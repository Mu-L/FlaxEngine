// Copyright (c) Wojciech Figat. All rights reserved.

#pragma once

#include "Light.h"
#include "Engine/Content/Assets/IESProfile.h"
#include "Engine/Content/AssetReference.h"

/// <summary>
/// Point light emits light from point in all directions.
/// </summary>
API_CLASS(Attributes="ActorContextMenu(\"New/Lights/Point Light\"), ActorToolbox(\"Lights\")")
class FLAXENGINE_API PointLight : public LightWithShadow
{
    DECLARE_SCENE_OBJECT(PointLight);
private:
    Float3 _direction;
    float _radius;

public:
    /// <summary>
    /// Light source bulb radius
    /// </summary>
    API_FIELD(Attributes="EditorOrder(2), DefaultValue(0.0f), EditorDisplay(\"Light\"), Limit(0, 1000, 0.01f)")
    float SourceRadius = 0.0f;

    /// <summary>
    /// Light source bulb length
    /// </summary>
    API_FIELD(Attributes="EditorOrder(3), DefaultValue(0.0f), EditorDisplay(\"Light\"), Limit(0, 1000, 0.01f)")
    float SourceLength = 0.0f;

    /// <summary>
    /// Whether to use physically based inverse squared distance falloff, where Radius is only clamping the light's contribution.
    /// </summary>
    API_FIELD(Attributes="EditorOrder(13), DefaultValue(false), EditorDisplay(\"Light\")")
    bool UseInverseSquaredFalloff = false;

    /// <summary>
    /// Controls the radial falloff of light when UseInverseSquaredFalloff is disabled.
    /// </summary>
    API_FIELD(Attributes="EditorOrder(14), DefaultValue(8.0f), EditorDisplay(\"Light\"), Limit(2, 16, 0.01f), VisibleIf(nameof(UseInverseSquaredFalloff), true)")
    float FallOffExponent = 8.0f;

    /// <summary>
    /// IES texture (light profiles from real world measured data)
    /// </summary>
    API_FIELD(Attributes="EditorOrder(211), DefaultValue(null), EditorDisplay(\"IES Profile\", \"IES Texture\")")
    AssetReference<IESProfile> IESTexture;

    /// <summary>
    /// Enable/disable using light brightness from IES profile
    /// </summary>
    API_FIELD(Attributes="EditorOrder(212), DefaultValue(false), EditorDisplay(\"IES Profile\", \"Use IES Brightness\")")
    bool UseIESBrightness = false;

    /// <summary>
    /// Global scale for IES brightness contribution
    /// </summary>
    API_FIELD(Attributes="EditorOrder(213), DefaultValue(1.0f), Limit(0, 10000, 0.01f), EditorDisplay(\"IES Profile\", \"Brightness Scale\")")
    float IESBrightnessScale = 1.0f;

public:
    /// <summary>
    /// Computes light brightness value.
    /// </summary>
    float ComputeBrightness() const;

    /// <summary>
    /// Gets scaled light radius
    /// </summary>
    float GetScaledRadius() const;

    /// <summary>
    /// Gets light radius
    /// </summary>
    API_PROPERTY(Attributes="EditorOrder(1), DefaultValue(1000.0f), EditorDisplay(\"Light\"), Limit(0, 100000, 0.1f)")
    FORCE_INLINE float GetRadius() const
    {
        return _radius;
    }

    /// <summary>
    /// Sets light radius
    /// </summary>
    /// <param name="value">The new value</param>
    API_PROPERTY() void SetRadius(float value);

private:
    void UpdateBounds();

public:
    // [LightWithShadow]
    void Draw(RenderContext& renderContext) override;
#if USE_EDITOR
    void OnDebugDraw() override;
    void OnDebugDrawSelected() override;
    void DrawLightsDebug(RenderView& view) override;
#endif
    void OnLayerChanged() override;
    void Serialize(SerializeStream& stream, const void* otherObj) override;
    void Deserialize(DeserializeStream& stream, ISerializeModifier* modifier) override;
    bool IntersectsItself(const Ray& ray, Real& distance, Vector3& normal) override;

protected:
    // [LightWithShadow]
    void OnTransformChanged() override;
};
