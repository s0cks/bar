#include "hypr_parser.h"

static inline char
parser_current(HyprParser* parser) {
  return parser->data[parser->rpos];
}

static inline char
parser_peek(HyprParser* parser) {
  const uint64_t next = parser->rpos + 1;
  if(next > parser->wpos)
    return '\0';
  return parser->data[next];
}

static inline char
parser_next(HyprParser* parser) {
  const char next = parser_current(parser);
  parser->rpos++;
  return next;
}

static inline bool
parser_is_eos(HyprParser* parser) {
  return parser_peek(parser) == '\0';
}

static inline bool
parse_event(HyprParser* parser) {
  uint64_t start_pos = parser->rpos;
  char curr = '\0';
  do {
    if(hypr_parser_has_error(parser)) {
      fprintf(stderr, "parser has error\n");
      return false;
    }
    else if(!hypr_parser_is(parser, kParsingEvent)) {
      fprintf(stderr, "invalid state: %s\n", hypr_parser_get_state_name(parser->state));
      hypr_parser_set_error(parser, kInvalidStateError);
      return false;
    }

    curr = parser_peek(parser);
    // fprintf(stdout, "[%s] current: %c\n", hypr_parser_get_state_name(parser->state), curr);
    switch(curr) {
      case '>': {
        parser_next(parser);
        if(parser_peek(parser) != '>') {
          fprintf(stderr, "invalid token\n");
          hypr_parser_set_error(parser, kInvalidTokenError);
          return false;
        }
        parser_next(parser);
        return true;
      }
      default:
        parser_next(parser);
        continue;
    }
  } while(true);
}

static inline bool
parse_event_data(HyprParser* parser) {
  char curr = '\0';
  do {
    if(hypr_parser_has_error(parser)) {
      fprintf(stderr, "parser has error\n");
      return false;
    }

    curr = parser_peek(parser);
    // fprintf(stdout, "[%s] current: %c\n", hypr_parser_get_state_name(parser->state), curr);
    switch(curr) {
      case '\n':
      case '\0':
      case ',':
        return true;
      default:
        parser_next(parser);
        continue;
    }
  } while(true);
}

bool hypr_parser_parse(HyprParser* parser) {
  if(parser->on_start) {
    if(!parser->on_start(parser))
      return false;
  }

  hypr_parser_set_state(parser, kParsingEvent);
  while(!parser_is_eos(parser) && hypr_parser_is(parser, kParsingEvent)) {
    const uint64_t event_start = parser->rpos;
    if(!parse_event(parser)) {
      fprintf(stderr, "failed to parse hypr event\n");
      return false;
    }

    const uint64_t event_end = parser->rpos;
    const uint64_t event_len = (event_end - event_start);
    char event[event_len];
    memcpy(&event[0], &parser->data[event_start], event_len);
    if(parser->on_event) {
      if(!parser->on_event(parser, event, event_len)) {
        fprintf(stderr, "on_event failed\n");
        return false;
      }
    }
    hypr_parser_set_state(parser, kParsingData);

  parse_data:
    const uint64_t data_start = parser->rpos;
    if(!parse_event_data(parser)) {
      fprintf(stderr, "failed to parse hypr event data\n");
      return false;
    }

    const uint64_t data_end = parser->rpos;
    const uint64_t data_len = (data_end - data_start);
    switch(parser_peek(parser)) {
      case '\r':
        parser_next(parser);
      case '\n': {
        parser_next(parser);

        char data[data_len];
        memcpy(&data[0], &parser->data[data_start], data_len);
        if(parser->on_data0) {
          if(!parser->on_data0(parser, data, data_len)) {
            fprintf(stderr, "on_data0 failed\n");
            return false;
          }
        }

        hypr_parser_set_state(parser, kParsingEvent);
        continue;
      }
      case ',': {
        parser_next(parser);

        char data[data_len];
        memcpy(&data[0], &parser->data[data_start], data_len);
        if(parser->on_data0) {
          if(!parser->on_data0(parser, data, data_len)) {
            fprintf(stderr, "on_data0 failed\n");
            return false;
          }
        }

        break;
      }
      case '\0': {
        char data[data_len];
        memcpy(&data[0], &parser->data[data_start], data_len);
        if(parser->on_data0) {
          if(!parser->on_data0(parser, data, data_len)) {
            fprintf(stderr, "on_data0 failed\n");
            return false;
          }
        }

        hypr_parser_set_state(parser, kParsingFinished);
        return true;
      }
      default:
        hypr_parser_set_error(parser, kInvalidTokenError);
        hypr_parser_set_state(parser, kParsingFinished);
        return false;
    }
  }

  // fprintf(stdout, "state: %s\n", hypr_parser_get_state_name(parser->state));
  // if(!hypr_parser_is(parser, kParsingFinished)) {
  //   fprintf(stderr, "parsing isnt finished\n");
  //   return false;
  // }

  //TODO: check for linebreak
  if(parser->on_finished) {
    if(!parser->on_finished(parser))
      return false;
  }
  return true;
}
