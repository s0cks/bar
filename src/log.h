#ifndef BAR_LOG_H
#define BAR_LOG_H

#define LOG(Message) \
  fprintf(stdout, "%s\n", (Message))
#define LOG_F(Format, ...) \
  fprintf(stdout, Format "\n", __VA_ARGS__)

#ifdef BAR_DEBUG

// define debug logging
#define DLOG(Message) \
  LOG(Message)
#define DLOG_F(Format, ...) \
  LOG_F(Format, __VA_ARGS__)

#else

// don't define debug logging
#define DLOG(Message)
#define DLOG_F(Format, ...)

#endif // BAR_DEBUG

#endif // BAR_LOG_H
