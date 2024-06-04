#pragma once

namespace wen {

enum class ShaderStage {
    eVertex,
    eFragment
};

enum class VertexType {
    eNone,
    eFloat,
    eFloat2,
    eFloat3,
    eFloat4,
    eInt,
    eInt2,
    eInt3,
    eInt4,
    eBool
};

} // namespace wen