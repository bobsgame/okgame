#ifndef CIMNODES_INCLUDED
#define CIMNODES_INCLUDED

#include <stddef.h>

//Replicated from https://github.com/cimgui/cimgui
#if defined _WIN32 || defined __CYGWIN__
    #ifdef CIMNODES_NO_EXPORT
        #define API
    #else
        #define API __declspec(dllexport)
    #endif
    #ifndef __GNUC__
    #define snprintf sprintf_s
    #endif
#else
    #define API
#endif

#if defined __cplusplus
    #define EXTERN extern "C"
#else
    #include <stdarg.h>
    #include <stdbool.h>
    #define EXTERN extern
#endif

#define CIMNODES_API EXTERN API
#define CONST const

#ifndef CIMGUI_INCLUDED
typedef struct ImVec2_Simple { float x; float y; } ImVec2_Simple;
#endif

#ifdef CIMNODES_DEFINE_ENUMS_AND_STRUCTS
typedef struct ImNodesIO ImNodesIO;
typedef struct ImNodesStyle ImNodesStyle;
typedef struct ImNodesEditorContext ImNodesEditorContext;
typedef enum ImNodesColorStyle ImNodesColorStyle;
typedef enum ImNodesStyleVar ImNodesStyleVar;
typedef enum ImNodesStyleFlags ImNodesStyleFlags;
typedef enum ImNodesPinShape ImNodesPinShape;
typedef enum ImNodesAttributeFlags ImNodesAttributeFlags;

#ifndef CIMGUI_INCLUDED
typedef struct ImVec2 ImVec2;
#endif

enum ImNodesColorStyle
{
    ImNodesColorStyle_ColorStyle_NodeBackground = 0,
    ImNodesColorStyle_ColorStyle_NodeBackgroundHovered,
    ImNodesColorStyle_ColorStyle_NodeBackgroundSelected,
    ImNodesColorStyle_ColorStyle_NodeOutline,
    ImNodesColorStyle_ColorStyle_TitleBar,
    ImNodesColorStyle_ColorStyle_TitleBarHovered,
    ImNodesColorStyle_ColorStyle_TitleBarSelected,
    ImNodesColorStyle_ColorStyle_Link,
    ImNodesColorStyle_ColorStyle_LinkHovered,
    ImNodesColorStyle_ColorStyle_LinkSelected,
    ImNodesColorStyle_ColorStyle_Pin,
    ImNodesColorStyle_ColorStyle_PinHovered,
    ImNodesColorStyle_ColorStyle_BoxSelector,
    ImNodesColorStyle_ColorStyle_BoxSelectorOutline,
    ImNodesColorStyle_ColorStyle_GridBackground,
    ImNodesColorStyle_ColorStyle_GridLine,
    ImNodesColorStyle_ColorStyle_Count
};

enum ImNodesStyleVar
{
    ImNodesStyleVar_StyleVar_GridSpacing = 0,
    ImNodesStyleVar_StyleVar_NodeCornerRounding,
    ImNodesStyleVar_StyleVar_NodePaddingHorizontal,
    ImNodesStyleVar_StyleVar_NodePaddingVertical
};

enum ImNodesStyleFlags
{
    ImNodesStyleFlags_StyleFlags_None = 0,
    ImNodesStyleFlags_StyleFlags_NodeOutline = 1 << 0,
    ImNodesStyleFlags_StyleFlags_GridLines = 1 << 2
};

// This enum controls the way attribute pins look.
enum ImNodesPinShape
{
    ImNodesPinShape_PinShape_Circle,
    ImNodesPinShape_PinShape_CircleFilled,
    ImNodesPinShape_PinShape_Triangle,
    ImNodesPinShape_PinShape_TriangleFilled,
    ImNodesPinShape_PinShape_Quad,
    ImNodesPinShape_PinShape_QuadFilled
};

// This enum controls the way the attribute pins behave.
enum ImNodesAttributeFlags
{
    ImNodesAttributeFlags_AttributeFlags_None = 0,
    // Allow detaching a link by left-clicking and dragging the link at a pin it
    // is connected to. NOTE: the user has to actually delete the link for this
    // to work. A deleted link can be detected by calling IsLinkDestroyed()
    // after EndNodeEditor().
    ImNodesAttributeFlags_AttributeFlags_EnableLinkDetachWithDragClick = 1 << 0
};

/*Structs*/

struct ImNodesIO
{
    struct EmulateThreeButtonMouse
    {
        // Controls whether this feature is enabled or not.
        bool enabled;
        const bool* modifier; // The keyboard modifier to use with the mouse
                              // left click. Set to &ImGuiIO::KeyAlt by default.
    } emulate_three_button_mouse;

    struct LinkDetachWithModifierClick
    {
        // Pointer to a boolean value indicating when the desired modifier is
        // pressed. Set to NULL by default (i.e. this feature is disabled). To
        // enable the feature, set the link to point to, for example,
        // &ImGuiIO::KeyCtrl.
        //
        // Left-clicking a link with this modifier pressed will detach that
        // link. NOTE: the user has to actually delete the link for this to
        // work. A deleted link can be detected by calling IsLinkDestroyed()
        // after EndNodeEditor().
        const bool* modifier;
    } link_detach_with_modifier_click;
};

struct ImNodesStyle
{
    float grid_spacing;

    float node_corner_rounding;
    float node_padding_horizontal;
    float node_padding_vertical;

    float link_thickness;
    float link_line_segments_per_length;
    float link_hover_distance;

    // The following variables control the look and behavior of the pins. The
    // default size of each pin shape is balanced to occupy approximately the
    // same surface area on the screen.

    // The circle radius used when the pin shape is either PinShape_Circle or
    // PinShape_CircleFilled.
    float pin_circle_radius;
    // The quad side length used when the shape is either PinShape_Quad or
    // PinShape_QuadFilled.
    float pin_quad_side_length;
    // The equilateral triangle side length used when the pin shape is either
    // PinShape_Triangle or PinShape_TriangleFilled.
    float pin_triangle_side_length;
    // The thickness of the line used when the pin shape is not filled.
    float pin_line_thickness;
    // The radius from the pin's center position inside of which it is detected
    // as being hovered over.
    float pin_hover_radius;
    // Offsets the pins' positions from the edge of the node to the outside of
    // the node.
    float pin_offset;

    // By default, StyleFlags_NodeOutline and StyleFlags_Gridlines are enabled.
    ImNodesStyleFlags flags;
    // Set these mid-frame using Push/PopColorStyle. You can index this color
    // array with with a ColorStyle enum value.
    unsigned int colors[ImNodesColorStyle_ColorStyle_Count];
};

struct ImNodesEditorContext;
#endif

CIMNODES_API ImNodesEditorContext* inodeEditorContextCreate();
CIMNODES_API void inodeEditorContextFree(ImNodesEditorContext* context);
CIMNODES_API void inodeEditorContextSet(ImNodesEditorContext* context);
CIMNODES_API ImVec2_Simple inodeEditorContextGetPanning();
CIMNODES_API void inodeEditorContextResetPanning(const ImVec2* pos);
CIMNODES_API void inodeEditorContextMoveToNode(const int node_id);

CIMNODES_API void inodeInitialize();
CIMNODES_API void inodeShutdown();

CIMNODES_API ImNodesIO* inodeGetIO();
CIMNODES_API ImNodesStyle* inodeGetStyle();

CIMNODES_API void inodeStyleColorsDark(); // on by default
CIMNODES_API void inodeStyleColorsClassic();
CIMNODES_API void inodeStyleColorsLight();

// The top-level function call. Call this before calling BeginNode/EndNode.
// Calling this function will result the node editor grid workspace being
// rendered.
CIMNODES_API void inodeBeginNodeEditor();
CIMNODES_API void inodeEndNodeEditor();

// Use PushColorStyle and PopColorStyle to modify Style::colors mid-frame.
CIMNODES_API void inodePushColorStyle(ImNodesColorStyle item, unsigned int color);
CIMNODES_API void inodePopColorStyle();
CIMNODES_API void inodePushStyleVar(ImNodesStyleVar style_item, float value);
CIMNODES_API void inodePopStyleVar();
CIMNODES_API void inodeBeginNode(int id);
CIMNODES_API void inodeEndNode();

// Place your node title bar content (such as the node title, using ImGui::Text)
// between the following function calls. These functions have to be called
// before adding any attributes, or the layout of the node will be incorrect.
CIMNODES_API void inodeBeginNodeTitleBar();
CIMNODES_API void inodeEndNodeTitleBar();

// Attributes are ImGui UI elements embedded within the node. Attributes have
// pin shapes rendered next to them. Links are created between pins.
//
// Input and output attributes are otherwise identical, except that pins are
// rendered on the left side of the node for input attributes, and on the right
// side for output attributes.
//
// The attribute ids must be unique.
CIMNODES_API void inodeBeginInputAttribute(int id, ImNodesPinShape shape);
CIMNODES_API void inodeBeginOutputAttribute(int id, ImNodesPinShape shape);
CIMNODES_API void inodeEndAttribute();

// Push a single AttributeFlags value. By default, only AttributeFlags_None is
// set.
CIMNODES_API void inodePushAttributeFlag(ImNodesAttributeFlags flag);
CIMNODES_API void inodePopAttributeFlag();

// Render a link between attributes.
// The attributes ids used here must match the ids used in
// Begin(Input|Output)Attribute function calls. The order of start_attr and
// end_attr doesn't make a difference for rendering the link.
CIMNODES_API void inodeLink(int id, int start_attribute_id, int end_attribute_id);

// Set's the node's position corresponding to the node id, either using screen
// space coordinates, or node editor grid coordinates. You can even set the
// position before the node has been created with BeginNode().

CIMNODES_API void inodeSetNodeScreenSpacePos(int node_id, const struct ImVec2* screen_space_pos);
CIMNODES_API void inodeSetNodeGridSpacePos(int node_id, const struct ImVec2* grid_pos);
// Enable or disable the ability to click and drag a specific node.
CIMNODES_API void inodeSetNodeDraggable(int node_id, const bool draggable);

// Returns true if the current node editor canvas is being hovered over by the
// mouse, and is not blocked by any other windows.
CIMNODES_API bool inodeIsEditorHovered();
// The following functions return true if a UI element is being hovered over by
// the mouse cursor. Assigns the id of the UI element being hovered over to the
// function argument. Use these functions after EndNodeEditor() has been called.
CIMNODES_API bool inodeIsNodeHovered(int* node_id);
CIMNODES_API bool inodeIsLinkHovered(int* link_id);
CIMNODES_API bool inodeIsPinHovered(int* attribute_id);

// Use The following two functions to query the number of selected nodes or
// links in the current editor. Use after calling EndNodeEditor().
CIMNODES_API int inodeNumSelectedNodes();
CIMNODES_API int inodeNumSelectedLinks();
// Get the selected node/link ids. The pointer argument should point to an
// integer array with at least as many elements as the respective
// NumSelectedNodes/NumSelectedLinks function call returned.
CIMNODES_API void inodeGetSelectedNodes(int* node_ids);
CIMNODES_API void inodeGetSelectedLinks(int* link_ids);

// Was the previous attribute active? This will continuously return true while
// the left mouse button is being pressed over the UI content of the attribute.
CIMNODES_API bool inodeIsAttributeActive();
// Was any attribute active? If so, sets the active attribute id to the output
// function argument.
CIMNODES_API bool inodeIsAnyAttributeActive(int* attribute_id);

// Use the following functions to query a change of state for an existing link,
// or new link. Call these after EndNodeEditor().

// Did the user start dragging a new link from a pin?
CIMNODES_API bool inodeIsLinkStarted(int* started_at_attribute_id);
// Did the user drop the dragged link before attaching it to a pin?
CIMNODES_API bool inodeIsLinkDropped();
// Did the user finish creating a new link?
CIMNODES_API bool inodeIsLinkCreated(int* started_at_attribute_id, int* ended_at_attribute_id);
// Was an existing link detached from a pin by the user? The detached link's id
// is assigned to the output argument link_id.
CIMNODES_API bool inodeIsLinkDestroyed(int* link_id);

// Use the following functions to write the editor context's state to a string,
// or directly to a file. The editor context is serialized in the INI file
// format.

CIMNODES_API const char* inodeSaveCurrentEditorStateToIniString(size_t* data_size);
CIMNODES_API const char* inodeSaveEditorStateToIniString(
    const ImNodesEditorContext* editor,
    size_t* data_size);

CIMNODES_API void inodeLoadCurrentEditorStateFromIniString(const char* data, size_t data_size);
CIMNODES_API void inodeLoadEditorStateFromIniString(
    ImNodesEditorContext* editor,
    const char* data,
    size_t data_size);

CIMNODES_API void inodeSaveCurrentEditorStateToIniFile(const char* file_name);
CIMNODES_API void inodeSaveEditorStateToIniFile(
    const ImNodesEditorContext* editor,
    const char* file_name);

CIMNODES_API void inodeLoadCurrentEditorStateFromIniFile(const char* file_name);
CIMNODES_API void inodeLoadEditorStateFromIniFile(ImNodesEditorContext* editor, const char* file_name);
#endif //CIMNODES_INCLUDED