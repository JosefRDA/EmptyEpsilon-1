#ifndef RADAR_VIEW_H
#define RADAR_VIEW_H

#include "gui/gui2_element.h"
#include "sectorsView.h"
#include "spaceObjects/playerSpaceship.h"
#include "gui/gui2_overlay.h"

class GuiMissileTubeControls;

class GuiRadarView : public SectorsView
{
public:
    enum ERadarStyle
    {
        Rectangular,
        Circular,
        CircularMasked
    };
    enum EFogOfWarStyle
    {
        NoFogOfWar,
        NebulaFogOfWar,
        FriendlysShortRangeFogOfWar,
        NoObjects
    };

    typedef std::function<void(sf::Vector2f position)> func_t;
    typedef std::function<void(float position)>        ffunc_t;
private:
    sf::RenderTexture background_texture;
    sf::RenderTexture forground_texture;
    sf::RenderTexture mask_texture;

    class GhostDot
    {
    public:
        constexpr static float total_lifetime = 60.0f;

        sf::Vector2f position;
        float end_of_life;

        GhostDot(sf::Vector2f pos) : position(pos), end_of_life(engine->getElapsedTime() + total_lifetime) {}
    };
    std::vector<GhostDot> ghost_dots;
    float next_ghost_dot_update;

    GuiMissileTubeControls* missile_tube_controls;

    P<PlayerSpaceship> target_spaceship;
    bool long_range;
    bool show_ghost_dots;
    bool show_waypoints;
    bool show_target_projection;
    bool show_missile_tubes;
    bool show_callsigns;
    bool show_heading_indicators;
    bool show_game_master_data;
    bool auto_center_on_my_ship;
    float range_indicator_step_size;
    ERadarStyle style;
    EFogOfWarStyle fog_style;
    func_t mouse_down_func;
    func_t mouse_drag_func;
    func_t mouse_up_func;
    ffunc_t joystick_x_func;
    ffunc_t joystick_y_func;
    ffunc_t joystick_z_func;
    ffunc_t joystick_r_func;
public:
    GuiRadarView(GuiContainer* owner, string id, float distance, TargetsContainer* targets, P<PlayerSpaceship> targetSpaceship);

    virtual void onDraw(sf::RenderTarget& window);

    virtual GuiRadarView* setDistance(float distance) { SectorsView::setDistance(distance); return this; }
    GuiRadarView* setRangeIndicatorStepSize(float step) { range_indicator_step_size = step; return this; }
    GuiRadarView* longRange() { long_range = true; return this; }
    GuiRadarView* shortRange() { long_range = false; return this; }
    GuiRadarView* enableGhostDots() { show_ghost_dots = true; return this; }
    GuiRadarView* disableGhostDots() { show_ghost_dots = false; return this; }
    GuiRadarView* enableWaypoints() { show_waypoints = true; return this; }
    GuiRadarView* disableWaypoints() { show_waypoints = false; return this; }
    GuiRadarView* enableTargetProjections(GuiMissileTubeControls* missile_tube_controls) { show_target_projection = true; this->missile_tube_controls = missile_tube_controls; return this; }
    GuiRadarView* disableTargetProjections() { show_target_projection = false; return this; }
    GuiRadarView* enableMissileTubeIndicators() { show_missile_tubes = true; return this; }
    GuiRadarView* disableMissileTubeIndicators() { show_missile_tubes = false; return this; }
    GuiRadarView* enableCallsigns() { show_callsigns = true; return this; }
    GuiRadarView* disableCallsigns() { show_callsigns = false; return this; }
    GuiRadarView* enableHeadingIndicators() { show_heading_indicators = true; return this; }
    GuiRadarView* disableHeadingIndicators() { show_heading_indicators = false; return this; }
    GuiRadarView* gameMaster() { show_game_master_data = true; return this; }
    GuiRadarView* setStyle(ERadarStyle style) { this->style = style; return this; }
    GuiRadarView* setFogOfWarStyle(EFogOfWarStyle style) { this->fog_style = style; return this; }
    bool getAutoCentering() { return auto_center_on_my_ship; }
    GuiRadarView* setAutoCentering(bool value) { this->auto_center_on_my_ship = value; return this; }
    virtual GuiRadarView* setCallbacks(func_t mouse_down_func, func_t mouse_drag_func, func_t mouse_up_func) { SectorsView::setCallbacks(mouse_down_func, mouse_drag_func, mouse_up_func); return this; }
    virtual GuiRadarView* setJoystickCallbacks(ffunc_t joystick_x_func, ffunc_t joystick_y_func, ffunc_t joystick_z_func, ffunc_t joystick_r_func)
        { SectorsView::setJoystickCallbacks(joystick_x_func, joystick_y_func, joystick_z_func, joystick_r_func); return this; }
    virtual GuiRadarView* setViewPosition(sf::Vector2f view_position) { SectorsView::setViewPosition(view_position); return this; }

    virtual bool onMouseDown(sf::Vector2f position);
    void setTargetSpaceship(P<PlayerSpaceship> targetSpaceship){target_spaceship = targetSpaceship;}

private:
    void updateGhostDots();
    void drawBackground(sf::RenderTarget& window);
    void drawNebulaBlockedAreas(sf::RenderTarget& window);
    void drawNoneFriendlyBlockedAreas(sf::RenderTarget& window);
    void drawFriendlyNotVisibleAreas(sf::RenderTarget& window);
    void drawGhostDots(sf::RenderTarget& window);
    void drawWaypoints(sf::RenderTarget& window);
    void drawRangeIndicators(sf::RenderTarget& window);
    void drawTargetProjections(sf::RenderTarget& window);
    void drawMissileTubes(sf::RenderTarget& window);
    void drawObjects(sf::RenderTarget& window_normal, sf::RenderTarget& window_alpha);
    void drawObjectsGM(sf::RenderTarget& window);
    void drawHeadingIndicators(sf::RenderTarget& window);
    void drawRadarCutoff(sf::RenderTarget& window);
};

#endif//RADAR_VIEW_H
