#define CIMNODES_DEFINE_ENUMS_AND_STRUCTS
#include "imgui.h"
#include "imgui_internal.h"
#include "cimnodes.h"
#include "imnodes.h"

CIMNODES_API ImNodesEditorContext* inodeEditorContextCreate()
{
    return reinterpret_cast<ImNodesEditorContext*>(imnodes::EditorContextCreate());
}
CIMNODES_API void inodeEditorContextFree(ImNodesEditorContext* context)
{
    return imnodes::EditorContextFree(reinterpret_cast<imnodes::EditorContext*>(context));
}
CIMNODES_API void inodeEditorContextSet(ImNodesEditorContext* context)
{
    return imnodes::EditorContextSet(reinterpret_cast<imnodes::EditorContext*>(context));
}
CIMNODES_API ImVec2_Simple inodeEditorContextGetPanning()
{
    ImVec2 result = imnodes::EditorContextGetPanning();
    return { result.x, result.y };
}
CIMNODES_API void inodeEditorContextResetPanning(const struct ImVec2* pos)
{
    return imnodes::EditorContextResetPanning(*pos);
}
CIMNODES_API void inodeEditorContextMoveToNode(const int node_id)
{
    return imnodes::EditorContextMoveToNode(node_id);
}

CIMNODES_API void inodeInitialize()
{
    return imnodes::Initialize();
}
CIMNODES_API void inodeShutdown()
{
    return imnodes::Shutdown();
}

CIMNODES_API ImNodesIO* inodeGetIO()
{
    return reinterpret_cast<ImNodesIO*>(&imnodes::GetIO());
}
CIMNODES_API ImNodesStyle* inodeGetStyle()
{
    return reinterpret_cast<ImNodesStyle*>(&imnodes::GetStyle());
}

CIMNODES_API void inodeStyleColorsDark()
{
    return imnodes::StyleColorsDark();
}
CIMNODES_API void inodeStyleColorsClassic()
{
    return imnodes::StyleColorsClassic();
}
CIMNODES_API void inodeStyleColorsLight()
{
    return imnodes::StyleColorsLight();
}

CIMNODES_API void inodeBeginNodeEditor()
{
    return imnodes::BeginNodeEditor();
}
CIMNODES_API void inodeEndNodeEditor()
{
    return imnodes::EndNodeEditor();
}

CIMNODES_API void inodePushColorStyle(ImNodesColorStyle item, unsigned int color)
{
    return imnodes::PushColorStyle((imnodes::ColorStyle)item, color);
}
CIMNODES_API void inodePopColorStyle()
{
    return imnodes::PopColorStyle();
}
CIMNODES_API void inodePushStyleVar(ImNodesStyleVar style_item, float value)
{
    return imnodes::PushStyleVar((imnodes::StyleVar)style_item, value);
}
CIMNODES_API void inodePopStyleVar()
{
    return imnodes::PopStyleVar();
}
CIMNODES_API void inodeBeginNode(int id)
{
    return imnodes::BeginNode(id);
}
CIMNODES_API void inodeEndNode()
{
    return imnodes::EndNode();
}

CIMNODES_API void inodeBeginNodeTitleBar()
{
    return imnodes::BeginNodeTitleBar();
}
CIMNODES_API void inodeEndNodeTitleBar()
{
    return imnodes::EndNodeTitleBar();
}

CIMNODES_API void inodeBeginInputAttribute(int id, ImNodesPinShape shape)
{
    return imnodes::BeginInputAttribute(id, (imnodes::PinShape)shape);
}
CIMNODES_API void inodeBeginOutputAttribute(int id, ImNodesPinShape shape)
{
    return imnodes::BeginOutputAttribute(id, (imnodes::PinShape)shape);
}
CIMNODES_API void inodeEndAttribute()
{
    return imnodes::EndAttribute();
}

CIMNODES_API void inodePushAttributeFlag(ImNodesAttributeFlags flag)
{
    return imnodes::PushAttributeFlag((imnodes::AttributeFlags)flag);
}
CIMNODES_API void inodePopAttributeFlag()
{
    return imnodes::PopAttributeFlag();
}

CIMNODES_API void inodeLink(int id, int start_attribute_id, int end_attribute_id)
{
    return imnodes::Link(id, start_attribute_id, end_attribute_id);
}

CIMNODES_API void inodeSetNodeScreenSpacePos(int node_id, const struct ImVec2* screen_space_pos)
{
    return imnodes::SetNodeScreenSpacePos(node_id, *screen_space_pos);
}
CIMNODES_API void inodeSetNodeGridSpacePos(int node_id, const struct ImVec2* grid_pos)
{
    return imnodes::SetNodeGridSpacePos(node_id, *grid_pos);
}
CIMNODES_API void inodeSetNodeDraggable(int node_id, const bool draggable)
{
    return imnodes::SetNodeDraggable(node_id, draggable);
}

CIMNODES_API bool inodeIsEditorHovered()
{
    return imnodes::IsEditorHovered();
}

CIMNODES_API bool inodeIsNodeHovered(int* node_id)
{
    return imnodes::IsNodeHovered(node_id);
}
CIMNODES_API bool inodeIsLinkHovered(int* link_id)
{
    return imnodes::IsLinkHovered(link_id);
}
CIMNODES_API bool inodeIsPinHovered(int* attribute_id)
{
    return imnodes::IsPinHovered(attribute_id);
}

CIMNODES_API int inodeNumSelectedNodes()
{
    return imnodes::NumSelectedNodes();
}
CIMNODES_API int inodeNumSelectedLinks()
{
    return imnodes::NumSelectedNodes();
}

CIMNODES_API void inodeGetSelectedNodes(int* node_ids)
{
    return imnodes::GetSelectedNodes(node_ids);
}
CIMNODES_API void inodeGetSelectedLinks(int* link_ids)
{
    return imnodes::GetSelectedLinks(link_ids);
}

CIMNODES_API bool inodeIsAttributeActive()
{
    return imnodes::IsAttributeActive();
}
CIMNODES_API bool inodeIsAnyAttributeActive(int* attribute_id)
{
    return imnodes::IsAnyAttributeActive(attribute_id);
}

CIMNODES_API bool inodeIsLinkStarted(int* started_at_attribute_id)
{
    return imnodes::IsLinkStarted(started_at_attribute_id);
}
CIMNODES_API bool inodeIsLinkDropped()
{
    return imnodes::IsLinkDropped();
}
CIMNODES_API bool inodeIsLinkCreated(int* started_at_attribute_id, int* ended_at_attribute_id)
{
    return imnodes::IsLinkCreated(started_at_attribute_id, ended_at_attribute_id);
}
CIMNODES_API bool inodeIsLinkDestroyed(int* link_id)
{
    return imnodes::IsLinkDestroyed(link_id);
}

CIMNODES_API const char* inodeSaveCurrentEditorStateToIniString(size_t* data_size)
{
    return imnodes::SaveCurrentEditorStateToIniString(data_size);
}
CIMNODES_API const char* inodeSaveEditorStateToIniString(const ImNodesEditorContext* editor, size_t* data_size)
{
    return imnodes::SaveEditorStateToIniString(reinterpret_cast<const imnodes::EditorContext*>(editor), data_size);
}

CIMNODES_API void inodeLoadCurrentEditorStateFromIniString(const char* data, size_t data_size)
{
    return imnodes::LoadCurrentEditorStateFromIniString(data, data_size);
}
CIMNODES_API void inodeLoadEditorStateFromIniString(ImNodesEditorContext* editor, const char* data, size_t data_size)
{
    return imnodes::LoadEditorStateFromIniString(reinterpret_cast<imnodes::EditorContext*>(editor), data, data_size);
}

CIMNODES_API void inodeSaveCurrentEditorStateToIniFile(const char* file_name)
{
    return imnodes::SaveCurrentEditorStateToIniFile(file_name);
}
CIMNODES_API void inodeSaveEditorStateToIniFile(const ImNodesEditorContext* editor, const char* file_name)
{
    return imnodes::SaveEditorStateToIniFile(reinterpret_cast<const imnodes::EditorContext*>(editor), file_name);
}

CIMNODES_API void inodeLoadCurrentEditorStateFromIniFile(const char* file_name)
{
    return imnodes::LoadCurrentEditorStateFromIniFile(file_name);
}
CIMNODES_API void inodeLoadEditorStateFromIniFile(ImNodesEditorContext* editor, const char* file_name)
{
    return imnodes::LoadEditorStateFromIniFile(reinterpret_cast<imnodes::EditorContext*>(editor), file_name);
}