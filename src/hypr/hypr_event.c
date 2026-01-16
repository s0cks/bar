#include "hypr_event.h"
#include <stdlib.h>
#include <string.h>

void hypr_event_workspace_init(WorkspaceEvent* event, const char* workspace) {
  event->workspace = strdup(workspace);
}

void hypr_event_workspacev2_init(Workspacev2Event* event, 
                                 const char* workspace_id,
                                 const char* workspace_name) {
  event->workspace_id = strdup(workspace_id);
  event->workspace_name = strdup(workspace_name);
}

void hypr_event_focusedmon_init(FocusedMonitorEvent* event,
                                    const char* monitor_name,
                                    const char* workspace_name) {
  event->monitor_name = strdup(monitor_name);
  event->workspace_name = strdup(workspace_name);
}

void hypr_event_focusedmonv2_init(FocusedMonitorv2Event* event,
                                    const char* monitor_name,
                                    const char* workspace_id) {
  event->monitor_name = strdup(monitor_name);
  event->workspace_id = strdup(workspace_id);
}

void hypr_event_activewindow_init(ActiveWindowEvent* event,
                                    const char* window_class,
                                    const char* window_title) {
  event->window_class = strdup(window_class);
  event->window_title = strdup(window_title);
}

void hypr_event_activewindowv2_init(ActiveWindowv2Event* event,
                                    const char* window_address) {
  event->window_address = strdup(window_address);
}

void hypr_event_fullscreen_init(FullscreenEvent* event,
                                    const bool state) {
  event->state = state;
}

void hypr_event_monitorremoved_init(MonitorRemovedEvent* event,
                                    const char* monitor_name) {
  event->monitor_name = strdup(monitor_name);
}

void hypr_event_monitorremovedv2_init(MonitorRemovedv2Event* event,
                                    const char* monitor_id,
                                    const char* monitor_name,
                                    const char* monitor_desc) {
  event->monitor_id = strdup(monitor_id);
  event->monitor_name = strdup(monitor_name);
  event->monitor_desc = strdup(monitor_desc);
}

void hypr_event_monitoradded_init(MonitorAddedEvent* event,
                                    const char* monitor_name) {
  event->monitor_name = strdup(monitor_name);
}

void hypr_event_monitoraddedv2_init(MonitorAddedv2Event* event,
                                    const char* monitor_id,
                                    const char* monitor_name,
                                    const char* monitor_desc) {
  event->monitor_id = strdup(monitor_id);
  event->monitor_name = strdup(monitor_name);
  event->monitor_desc = strdup(monitor_desc);
}

void hypr_event_createworkspace_init(CreateWorkspaceEvent* event,
                                    const char* workspace_name) {
  event->workspace_name = strdup(workspace_name);
}

void hypr_event_createworkspacev2_init(CreateWorkspacev2Event* event,
                                    const char* workspace_id,
                                    const char* workspace_name) {
  event->workspace_id = strdup(workspace_id);
  event->workspace_name = strdup(workspace_name);
}

void hypr_event_destroyworkspace_init(DestroyWorkspaceEvent* event,
                                    const char* workspace_name) {
  event->workspace_name = strdup(workspace_name);
}

void hypr_event_destroyworkspacev2_init(DestroyWorkspacev2Event* event,
                                    const char* workspace_id,
                                    const char* workspace_name) {
  event->workspace_id = strdup(workspace_id);
  event->workspace_name = strdup(workspace_name);
}

void hypr_event_moveworkspace_init(MoveWorkspaceEvent* event,
                                    const char* workspace_name,
                                    const char* monitor_name) {
  event->workspace_name = strdup(workspace_name);
  event->monitor_name = strdup(monitor_name);
}

void hypr_event_moveworkspacev2_init(MoveWorkspacev2Event* event,
                                    const char* workspace_id,
                                    const char* workspace_name,
                                    const char* monitor_name) {
  event->workspace_id = strdup(workspace_id);
  event->workspace_name = strdup(workspace_name);
  event->monitor_name = strdup(monitor_name);
}

void hypr_event_renameworkspace_init(RenameWorkspaceEvent* event,
                                    const char* workspace_id,
                                    const char* new_name) {
  event->workspace_id = strdup(workspace_id);
  event->name = strdup(new_name);
}

void hypr_event_activespecial_init(ActiveSpecialEvent* event,
                                    const char* workspace_name,
                                    const char* monitor_name) {
  event->workspace_name = strdup(workspace_name);
  event->monitor_name = strdup(monitor_name);
}

void hypr_event_activespecialv2_init(ActiveSpecialv2Event* event,
                                    const char* workspace_id,
                                    const char* workspace_name,
                                    const char* monitor_name) {
  event->workspace_id = strdup(workspace_id);
  event->workspace_name = strdup(workspace_name);
  event->monitor_name = strdup(monitor_name);
}

void hypr_event_activelayout_init(ActiveLayoutEvent* event,
                                    const char* keyboard_name,
                                    const char* layout_name) {
  event->keyboard_name = strdup(keyboard_name);
  event->layout_name = strdup(layout_name);
}

void hypr_event_openwindow_init(OpenWindowEvent* event,
                                    const char* window_address,
                                    const char* workspace_name,
                                    const char* window_class,
                                    const char* window_title) {
  event->window_address = strdup(window_address);
  event->workspace_name = strdup(workspace_name);
  event->window_class = strdup(window_class);
  event->window_title = strdup(window_title);
}

void hypr_event_closewindow_init(CloseWindowEvent* event,
                                    const char* window_address) {
  event->window_address = strdup(window_address);
}

void hypr_event_movewindow_init(MoveWindowEvent* event,
                                    const char* window_address,
                                    const char* workspace_name) {
  event->window_address = strdup(window_address);
  event->workspace_name = strdup(workspace_name);
}

void hypr_event_movewindowv2_init(MoveWindowv2Event* event,
                                    const char* window_address,
                                    const char* workspace_id,
                                    const char* workspace_name) {
  event->window_address = strdup(window_address);
  event->workspace_id = strdup(workspace_id);
  event->workspace_name = strdup(workspace_name);
}

void hypr_event_openlayer_init(OpenLayerEvent* event,
                                    const char* namespace) {
  event->namespace = strdup(namespace);
}

void hypr_event_closelayer_init(CloseLayerEvent* event,
                                    const char* namespace) {
  event->namespace = strdup(namespace);
}

void hypr_event_submap_init(SubmapEvent* event,
                                    const char* submapname) {
  event->submapname = strdup(submapname);
}

void hypr_event_changefloatingmode_init(ChangeFloatingModeEvent* event,
                                    const char* window_address,
                                    const bool state) {
  event->window_address = strdup(window_address);
  event->state = state;
}

void hypr_event_urgent_init(UrgentEvent* event,
                                    const char* window_address) {
  event->window_address = strdup(window_address);
}

void hypr_event_screencast_init(ScreencastEvent* event,
                                    const bool state,
                                    const char* owner) {
  event->state = state;
  event->owner = strdup(owner);
}

void hypr_event_windowtitle_init(WindowTitleEvent* event,
                                    const char* window_address) {
  event->window_address = strdup(window_address);
}

void hypr_event_windowtitlev2_init(WindowTitlev2Event* event,
                                    const char* window_address,
                                    const char* window_title) {
  event->window_address = strdup(window_address);
  event->window_title = strdup(window_title);
}

void hypr_event_togglegroup_init(ToggleGroupEvent* event,
                                    const bool state,
                                    const char** window_addresses,
                                    const uint64_t num_window_addresses) {
  event->state = state;
  event->window_addresses = window_addresses;
  event->num_window_addresses = num_window_addresses;
}

void hypr_event_moveintogroup_init(MoveIntoGroupEvent* event,
                                    const char* window_address) {
  event->window_address = strdup(window_address);
}

void hypr_event_moveoutofgroup_init(MoveOutOfGroupEvent* event,
                                    const char* window_address) {
  event->window_address = strdup(window_address);
}

void hypr_event_ignoregrouplock_init(IgnoreGroupLockEvent* event,
                                    const bool state) {
event->state = state;
}

void hypr_event_lockgroups_init(LockGroupsEvent* event,
                                    const bool state) {
event->state = state;
}

void hypr_event_configreloaded_init(ConfigReloadedEvent* event) {
}

void hypr_event_pin_init(PinEvent* event,
                         const char* window_address,
                         const bool state) {
  event->window_address = strdup(window_address);
  event->state = state;
}

void hypr_event_minimized_init(MinimizedEvent* event,
                               const char* window_address) {
  event->window_address = strdup(window_address);
}

void hypr_event_bell_init(BellEvent* event) {

}

void hypr_event_workspace_free(WorkspaceEvent* event) {
  if(event->workspace)
    free(event->workspace);
}

void hypr_event_workspacev2_free(Workspacev2Event* event) {
  if(event->workspace_id)
    free(event->workspace_id);
  if(event->workspace_name)
    free(event->workspace_name);
}

void hypr_event_focusedmon_free(FocusedMonitorEvent* event) {
  if(event->monitor_name)
    free(event->monitor_name);
  if(event->workspace_name)
    free(event->workspace_name);
}

void hypr_event_focusedmonv2_free(FocusedMonitorv2Event* event) {
  if(event->monitor_name)
    free(event->monitor_name);
  if(event->workspace_id)
    free(event->workspace_id);
}

void hypr_event_activewindow_free(ActiveWindowEvent* event) {
  if(event->window_class)
    free(event->window_class);
  if(event->window_title)
    free(event->window_title);
}

void hypr_event_activewindowv2_free(ActiveWindowv2Event* event) {
  if(event->window_address)
    free(event->window_address);
}

void hypr_event_fullscreen_free(FullscreenEvent* event) { }

void hypr_event_monitorremoved_free(MonitorRemovedEvent* event) {
  if(event->monitor_name)
    free(event->monitor_name);
}

void hypr_event_monitorremovedv2_free(MonitorRemovedv2Event* event) {
  if(event->monitor_id)
    free(event->monitor_id);
  if(event->monitor_name)
    free(event->monitor_name);
  if(event->monitor_desc)
    free(event->monitor_desc);
}

void hypr_event_monitoradded_free(MonitorAddedEvent* event) {
  if(event->monitor_name)
    free(event->monitor_name);
}

void hypr_event_monitoraddedv2_free(MonitorAddedv2Event* event) {
  if(event->monitor_id)
    free(event->monitor_id);
  if(event->monitor_name)
    free(event->monitor_name);
  if(event->monitor_desc)
    free(event->monitor_desc);
}

void hypr_event_createworkspace_free(CreateWorkspaceEvent* event) {
  if(event->workspace_name)
    free(event->workspace_name);
}

void hypr_event_createworkspacev2_free(CreateWorkspacev2Event* event) {
  if(event->workspace_id)
    free(event->workspace_id);
  if(event->workspace_name)
    free(event->workspace_name);
}

void hypr_event_destroyworkspace_free(DestroyWorkspaceEvent* event) {
  if(event->workspace_name)
    free(event->workspace_name);
}

void hypr_event_destroyworkspacev2_free(DestroyWorkspacev2Event* event) {
  if(event->workspace_id)
    free(event->workspace_id);
  if(event->workspace_name)
    free(event->workspace_name);
}

void hypr_event_moveworkspace_free(MoveWorkspaceEvent* event) {
  if(event->workspace_name)
    free(event->workspace_name);
  if(event->monitor_name)
    free(event->monitor_name);
}

void hypr_event_moveworkspacev2_free(MoveWorkspacev2Event* event) {
  if(event->workspace_id)
    free(event->workspace_id);
  if(event->workspace_name)
    free(event->workspace_name);
  if(event->monitor_name)
    free(event->monitor_name);
}

void hypr_event_renameworkspace_free(RenameWorkspaceEvent* event) {
  if(event->workspace_id)
    free(event->workspace_id);
  if(event->name)
    free(event->name);
}

void hypr_event_activespecial_free(ActiveSpecialEvent* event) {
  if(event->workspace_name)
    free(event->workspace_name);
  if(event->monitor_name)
    free(event->monitor_name);
}

void hypr_event_activespecialv2_free(ActiveSpecialv2Event* event) {
  if(event->workspace_id)
    free(event->workspace_id);
  if(event->workspace_name)
    free(event->workspace_name);
  if(event->monitor_name)
    free(event->monitor_name);
}

void hypr_event_activelayout_free(ActiveLayoutEvent* event) {
  if(event->keyboard_name)
    free(event->keyboard_name);
  if(event->layout_name)
    free(event->layout_name);
}

void hypr_event_openwindow_free(OpenWindowEvent* event) {
  if(event->window_address)
    free(event->window_address);
  if(event->workspace_name)
    free(event->workspace_name);
  if(event->window_class)
    free(event->window_class);
  if(event->window_title)
    free(event->window_title);
}

void hypr_event_closewindow_free(CloseWindowEvent* event) {
  if(event->window_address)
    free(event->window_address);
}

void hypr_event_movewindow_free(MoveWindowEvent* event) {
  if(event->window_address)
    free(event->window_address);
  if(event->workspace_name)
    free(event->workspace_name);
}

void hypr_event_movewindowv2_free(MoveWindowv2Event* event) {
  if(event->window_address)
    free(event->window_address);
  if(event->workspace_id)
    free(event->workspace_id);
  if(event->workspace_name)
    free(event->workspace_name);
}

void hypr_event_openlayer_free(OpenLayerEvent* event) {
  if(event->namespace)
    free(event->namespace);
}

void hypr_event_closelayer_free(CloseLayerEvent* event) {
  if(event->namespace)
    free(event->namespace);
}

void hypr_event_submap_free(SubmapEvent* event) {
  if(event->submapname)
    free(event->submapname);
}

void hypr_event_changefloatingmode_free(ChangeFloatingModeEvent* event) {
  if(event->window_address)
    free(event->window_address);
}

void hypr_event_urgent_free(UrgentEvent* event) {
  if(event->window_address)
    free(event->window_address);
}

void hypr_event_screencast_free(ScreencastEvent* event) {
  if(event->owner)
    free(event->owner);
}

void hypr_event_windowtitle_free(WindowTitleEvent* event) {
  if(event->window_address)
    free(event->window_address);
}

void hypr_event_windowtitlev2_free(WindowTitlev2Event* event) {
  if(event->window_address)
    free(event->window_address);
  if(event->window_title)
    free(event->window_title);
}

void hypr_event_togglegroup_free(ToggleGroupEvent* event) {
  if(event->window_addresses)
    free(event->window_addresses);
}

void hypr_event_moveintogroup_free(MoveIntoGroupEvent* event) {
  if(event->window_address)
    free(event->window_address);
}

void hypr_event_moveoutofgroup_free(MoveOutOfGroupEvent* event) {
  if(event->window_address)
    free(event->window_address);
}

void hypr_event_ignoregrouplock_free(IgnoreGroupLockEvent* event) { }

void hypr_event_lockgroups_free(LockGroupsEvent* event) { }

void hypr_event_configreloaded_free(ConfigReloadedEvent* event) {
  // no fields
}

void hypr_event_pin_free(PinEvent* event) {
  if(event->window_address)
    free(event->window_address);
}

void hypr_event_minimized_free(MinimizedEvent* event) {
  //TODO(@s0cks): free window_address;
}

void hypr_event_bell_free(BellEvent* event) {
  if(event->window_address)
    free(event->window_address);
}


// connected!
// hyprland event: openlayer>>gtk4-layer-shell
//
//
// number of args: 3
//
// hyprland event: activewindow>>google-chrome,zserge/lua-promises: A+ promises in Lua - Google Chrome
// activewindowv2>>56487f27ea70
//
//
// hyprland event: activewindow>>org.wezfurlong.wezterm,tazz@tazz-xps: ~proj/bar
// activewindowv2>>56487f1d2280
//
//
// hyprland event: activewindow>>org.wezfurlong.wezterm,tazz@tazz-xps: ~proj/bar
// activewindowv2>>56487f1d2280
//
//                                                           hyprland event: activewindow>>org.wezfurlong.wezterm,tazz@tazz-xps: ~proj/bar
// activewindowv2>>56487f1d2280
