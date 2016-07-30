static const spv_operand_desc_t pygen_variable_ImageOperandsEntries[] = {
  {"None", 0x0000, 0x0000, {}},
  {"Bias", 0x0001, 0x0002, {SPV_OPERAND_TYPE_ID}},
  {"Lod", 0x0002, 0x0000, {SPV_OPERAND_TYPE_ID}},
  {"Grad", 0x0004, 0x0000, {SPV_OPERAND_TYPE_ID, SPV_OPERAND_TYPE_ID}},
  {"ConstOffset", 0x0008, 0x0000, {SPV_OPERAND_TYPE_ID}},
  {"Offset", 0x0010, 0x2000000, {SPV_OPERAND_TYPE_ID}},
  {"ConstOffsets", 0x0020, 0x0000, {SPV_OPERAND_TYPE_ID}},
  {"Sample", 0x0040, 0x0000, {SPV_OPERAND_TYPE_ID}},
  {"MinLod", 0x0080, 0x40000000000, {SPV_OPERAND_TYPE_ID}}
};

static const spv_operand_desc_t pygen_variable_FPFastMathModeEntries[] = {
  {"None", 0x0000, 0x0000, {}},
  {"NotNaN", 0x0001, 0x0040, {}},
  {"NotInf", 0x0002, 0x0040, {}},
  {"NSZ", 0x0004, 0x0040, {}},
  {"AllowRecip", 0x0008, 0x0040, {}},
  {"Fast", 0x0010, 0x0040, {}}
};

static const spv_operand_desc_t pygen_variable_SelectionControlEntries[] = {
  {"None", 0x0000, 0x0000, {}},
  {"Flatten", 0x0001, 0x0000, {}},
  {"DontFlatten", 0x0002, 0x0000, {}}
};

static const spv_operand_desc_t pygen_variable_LoopControlEntries[] = {
  {"None", 0x0000, 0x0000, {}},
  {"Unroll", 0x0001, 0x0000, {}},
  {"DontUnroll", 0x0002, 0x0000, {}}
};

static const spv_operand_desc_t pygen_variable_FunctionControlEntries[] = {
  {"None", 0x0000, 0x0000, {}},
  {"Inline", 0x0001, 0x0000, {}},
  {"DontInline", 0x0002, 0x0000, {}},
  {"Pure", 0x0004, 0x0000, {}},
  {"Const", 0x0008, 0x0000, {}}
};

static const spv_operand_desc_t pygen_variable_MemorySemanticsEntries[] = {
  {"Relaxed", 0x0000, 0x0000, {}},
  {"None", 0x0000, 0x0000, {}},
  {"SequentiallyConsistent", 0x0010, 0x0000, {}},
  {"Acquire", 0x0002, 0x0000, {}},
  {"Release", 0x0004, 0x0000, {}},
  {"AcquireRelease", 0x0008, 0x0000, {}},
  {"UniformMemory", 0x0040, 0x0002, {}},
  {"SubgroupMemory", 0x0080, 0x0000, {}},
  {"WorkgroupMemory", 0x0100, 0x0000, {}},
  {"CrossWorkgroupMemory", 0x0200, 0x0000, {}},
  {"AtomicCounterMemory", 0x0400, 0x200000, {}},
  {"ImageMemory", 0x0800, 0x0000, {}}
};

static const spv_operand_desc_t pygen_variable_MemoryAccessEntries[] = {
  {"None", 0x0000, 0x0000, {}},
  {"Volatile", 0x0001, 0x0000, {}},
  {"Aligned", 0x0002, 0x0000, {SPV_OPERAND_TYPE_LITERAL_INTEGER}},
  {"Nontemporal", 0x0004, 0x0000, {}}
};

static const spv_operand_desc_t pygen_variable_KernelProfilingInfoEntries[] = {
  {"None", 0x0000, 0x0000, {}},
  {"CmdExecTime", 0x0001, 0x0040, {}}
};

static const spv_operand_desc_t pygen_variable_SourceLanguageEntries[] = {
  {"Unknown", 0, 0x0000, {}},
  {"ESSL", 1, 0x0000, {}},
  {"GLSL", 2, 0x0000, {}},
  {"OpenCL_C", 3, 0x0000, {}},
  {"OpenCL_CPP", 4, 0x0000, {}}
};

static const spv_operand_desc_t pygen_variable_ExecutionModelEntries[] = {
  {"Vertex", 0, 0x0002, {}},
  {"TessellationControl", 1, 0x0008, {}},
  {"TessellationEvaluation", 2, 0x0008, {}},
  {"Geometry", 3, 0x0004, {}},
  {"Fragment", 4, 0x0002, {}},
  {"GLCompute", 5, 0x0002, {}},
  {"Kernel", 6, 0x0040, {}}
};

static const spv_operand_desc_t pygen_variable_AddressingModelEntries[] = {
  {"Logical", 0, 0x0000, {}},
  {"Physical32", 1, 0x0010, {}},
  {"Physical64", 2, 0x0010, {}}
};

static const spv_operand_desc_t pygen_variable_MemoryModelEntries[] = {
  {"Simple", 0, 0x0002, {}},
  {"GLSL450", 1, 0x0002, {}},
  {"OpenCL", 2, 0x0040, {}}
};

static const spv_operand_desc_t pygen_variable_ExecutionModeEntries[] = {
  {"Invocations", 0, 0x0004, {SPV_OPERAND_TYPE_LITERAL_INTEGER}},
  {"SpacingEqual", 1, 0x0008, {}},
  {"SpacingFractionalEven", 2, 0x0008, {}},
  {"SpacingFractionalOdd", 3, 0x0008, {}},
  {"VertexOrderCw", 4, 0x0008, {}},
  {"VertexOrderCcw", 5, 0x0008, {}},
  {"PixelCenterInteger", 6, 0x0002, {}},
  {"OriginUpperLeft", 7, 0x0002, {}},
  {"OriginLowerLeft", 8, 0x0002, {}},
  {"EarlyFragmentTests", 9, 0x0002, {}},
  {"PointMode", 10, 0x0008, {}},
  {"Xfb", 11, 0x20000000000000, {}},
  {"DepthReplacing", 12, 0x0002, {}},
  {"DepthGreater", 14, 0x0002, {}},
  {"DepthLess", 15, 0x0002, {}},
  {"DepthUnchanged", 16, 0x0002, {}},
  {"LocalSize", 17, 0x0000, {SPV_OPERAND_TYPE_LITERAL_INTEGER, SPV_OPERAND_TYPE_LITERAL_INTEGER, SPV_OPERAND_TYPE_LITERAL_INTEGER}},
  {"LocalSizeHint", 18, 0x0040, {SPV_OPERAND_TYPE_LITERAL_INTEGER, SPV_OPERAND_TYPE_LITERAL_INTEGER, SPV_OPERAND_TYPE_LITERAL_INTEGER}},
  {"InputPoints", 19, 0x0004, {}},
  {"InputLines", 20, 0x0004, {}},
  {"InputLinesAdjacency", 21, 0x0004, {}},
  {"Triangles", 22, 0x000c, {}},
  {"InputTrianglesAdjacency", 23, 0x0004, {}},
  {"Quads", 24, 0x0008, {}},
  {"Isolines", 25, 0x0008, {}},
  {"OutputVertices", 26, 0x000c, {SPV_OPERAND_TYPE_LITERAL_INTEGER}},
  {"OutputPoints", 27, 0x0004, {}},
  {"OutputLineStrip", 28, 0x0004, {}},
  {"OutputTriangleStrip", 29, 0x0004, {}},
  {"VecTypeHint", 30, 0x0040, {SPV_OPERAND_TYPE_LITERAL_INTEGER}},
  {"ContractionOff", 31, 0x0040, {}}
};

static const spv_operand_desc_t pygen_variable_StorageClassEntries[] = {
  {"UniformConstant", 0, 0x0000, {}},
  {"Input", 1, 0x0002, {}},
  {"Uniform", 2, 0x0002, {}},
  {"Output", 3, 0x0002, {}},
  {"Workgroup", 4, 0x0000, {}},
  {"CrossWorkgroup", 5, 0x0000, {}},
  {"Private", 6, 0x0002, {}},
  {"Function", 7, 0x0000, {}},
  {"Generic", 8, 0x4000000000, {}},
  {"PushConstant", 9, 0x0002, {}},
  {"AtomicCounter", 10, 0x200000, {}},
  {"Image", 11, 0x0000, {}}
};

static const spv_operand_desc_t pygen_variable_DimEntries[] = {
  {"1D", 0, 0x80000000000, {}},
  {"2D", 1, 0x0000, {}},
  {"3D", 2, 0x0000, {}},
  {"Cube", 3, 0x0002, {}},
  {"Rect", 4, 0x2000000000, {}},
  {"Buffer", 5, 0x400000000000, {}},
  {"SubpassData", 6, 0x10000000000, {}}
};

static const spv_operand_desc_t pygen_variable_SamplerAddressingModeEntries[] = {
  {"None", 0, 0x0040, {}},
  {"ClampToEdge", 1, 0x0040, {}},
  {"Clamp", 2, 0x0040, {}},
  {"Repeat", 3, 0x0040, {}},
  {"RepeatMirrored", 4, 0x0040, {}}
};

static const spv_operand_desc_t pygen_variable_SamplerFilterModeEntries[] = {
  {"Nearest", 0, 0x0040, {}},
  {"Linear", 1, 0x0040, {}}
};

static const spv_operand_desc_t pygen_variable_ImageFormatEntries[] = {
  {"Unknown", 0, 0x0000, {}},
  {"Rgba32f", 1, 0x0002, {}},
  {"Rgba16f", 2, 0x0002, {}},
  {"R32f", 3, 0x0002, {}},
  {"Rgba8", 4, 0x0002, {}},
  {"Rgba8Snorm", 5, 0x0002, {}},
  {"Rg32f", 6, 0x2000000000000, {}},
  {"Rg16f", 7, 0x2000000000000, {}},
  {"R11fG11fB10f", 8, 0x2000000000000, {}},
  {"R16f", 9, 0x2000000000000, {}},
  {"Rgba16", 10, 0x2000000000000, {}},
  {"Rgb10A2", 11, 0x2000000000000, {}},
  {"Rg16", 12, 0x2000000000000, {}},
  {"Rg8", 13, 0x2000000000000, {}},
  {"R16", 14, 0x2000000000000, {}},
  {"R8", 15, 0x2000000000000, {}},
  {"Rgba16Snorm", 16, 0x2000000000000, {}},
  {"Rg16Snorm", 17, 0x2000000000000, {}},
  {"Rg8Snorm", 18, 0x2000000000000, {}},
  {"R16Snorm", 19, 0x2000000000000, {}},
  {"R8Snorm", 20, 0x2000000000000, {}},
  {"Rgba32i", 21, 0x0002, {}},
  {"Rgba16i", 22, 0x0002, {}},
  {"Rgba8i", 23, 0x0002, {}},
  {"R32i", 24, 0x0002, {}},
  {"Rg32i", 25, 0x2000000000000, {}},
  {"Rg16i", 26, 0x2000000000000, {}},
  {"Rg8i", 27, 0x2000000000000, {}},
  {"R16i", 28, 0x2000000000000, {}},
  {"R8i", 29, 0x2000000000000, {}},
  {"Rgba32ui", 30, 0x0002, {}},
  {"Rgba16ui", 31, 0x0002, {}},
  {"Rgba8ui", 32, 0x0002, {}},
  {"R32ui", 33, 0x0002, {}},
  {"Rgb10a2ui", 34, 0x2000000000000, {}},
  {"Rg32ui", 35, 0x2000000000000, {}},
  {"Rg16ui", 36, 0x2000000000000, {}},
  {"Rg8ui", 37, 0x2000000000000, {}},
  {"R16ui", 38, 0x2000000000000, {}},
  {"R8ui", 39, 0x2000000000000, {}}
};

static const spv_operand_desc_t pygen_variable_ImageChannelOrderEntries[] = {
  {"R", 0, 0x0040, {}},
  {"A", 1, 0x0040, {}},
  {"RG", 2, 0x0040, {}},
  {"RA", 3, 0x0040, {}},
  {"RGB", 4, 0x0040, {}},
  {"RGBA", 5, 0x0040, {}},
  {"BGRA", 6, 0x0040, {}},
  {"ARGB", 7, 0x0040, {}},
  {"Intensity", 8, 0x0040, {}},
  {"Luminance", 9, 0x0040, {}},
  {"Rx", 10, 0x0040, {}},
  {"RGx", 11, 0x0040, {}},
  {"RGBx", 12, 0x0040, {}},
  {"Depth", 13, 0x0040, {}},
  {"DepthStencil", 14, 0x0040, {}},
  {"sRGB", 15, 0x0040, {}},
  {"sRGBx", 16, 0x0040, {}},
  {"sRGBA", 17, 0x0040, {}},
  {"sBGRA", 18, 0x0040, {}},
  {"ABGR", 19, 0x0040, {}}
};

static const spv_operand_desc_t pygen_variable_ImageChannelDataTypeEntries[] = {
  {"SnormInt8", 0, 0x0040, {}},
  {"SnormInt16", 1, 0x0040, {}},
  {"UnormInt8", 2, 0x0040, {}},
  {"UnormInt16", 3, 0x0040, {}},
  {"UnormShort565", 4, 0x0040, {}},
  {"UnormShort555", 5, 0x0040, {}},
  {"UnormInt101010", 6, 0x0040, {}},
  {"SignedInt8", 7, 0x0040, {}},
  {"SignedInt16", 8, 0x0040, {}},
  {"SignedInt32", 9, 0x0040, {}},
  {"UnsignedInt8", 10, 0x0040, {}},
  {"UnsignedInt16", 11, 0x0040, {}},
  {"UnsignedInt32", 12, 0x0040, {}},
  {"HalfFloat", 13, 0x0040, {}},
  {"Float", 14, 0x0040, {}},
  {"UnormInt24", 15, 0x0040, {}},
  {"UnormInt101010_2", 16, 0x0040, {}}
};

static const spv_operand_desc_t pygen_variable_FPRoundingModeEntries[] = {
  {"RTE", 0, 0x0040, {}},
  {"RTZ", 1, 0x0040, {}},
  {"RTP", 2, 0x0040, {}},
  {"RTN", 3, 0x0040, {}}
};

static const spv_operand_desc_t pygen_variable_LinkageTypeEntries[] = {
  {"Export", 0, 0x0020, {}},
  {"Import", 1, 0x0020, {}}
};

static const spv_operand_desc_t pygen_variable_AccessQualifierEntries[] = {
  {"ReadOnly", 0, 0x0040, {}},
  {"WriteOnly", 1, 0x0040, {}},
  {"ReadWrite", 2, 0x0040, {}}
};

static const spv_operand_desc_t pygen_variable_FunctionParameterAttributeEntries[] = {
  {"Zext", 0, 0x0040, {}},
  {"Sext", 1, 0x0040, {}},
  {"ByVal", 2, 0x0040, {}},
  {"Sret", 3, 0x0040, {}},
  {"NoAlias", 4, 0x0040, {}},
  {"NoCapture", 5, 0x0040, {}},
  {"NoWrite", 6, 0x0040, {}},
  {"NoReadWrite", 7, 0x0040, {}}
};

static const spv_operand_desc_t pygen_variable_DecorationEntries[] = {
  {"RelaxedPrecision", 0, 0x0002, {}},
  {"SpecId", 1, 0x0002, {SPV_OPERAND_TYPE_LITERAL_INTEGER}},
  {"Block", 2, 0x0002, {}},
  {"BufferBlock", 3, 0x0002, {}},
  {"RowMajor", 4, 0x0001, {}},
  {"ColMajor", 5, 0x0001, {}},
  {"ArrayStride", 6, 0x0002, {SPV_OPERAND_TYPE_LITERAL_INTEGER}},
  {"MatrixStride", 7, 0x0001, {SPV_OPERAND_TYPE_LITERAL_INTEGER}},
  {"GLSLShared", 8, 0x0002, {}},
  {"GLSLPacked", 9, 0x0002, {}},
  {"CPacked", 10, 0x0040, {}},
  {"BuiltIn", 11, 0x0000, {SPV_OPERAND_TYPE_BUILT_IN}},
  {"NoPerspective", 13, 0x0002, {}},
  {"Flat", 14, 0x0002, {}},
  {"Patch", 15, 0x0008, {}},
  {"Centroid", 16, 0x0002, {}},
  {"Sample", 17, 0x800000000, {}},
  {"Invariant", 18, 0x0002, {}},
  {"Restrict", 19, 0x0000, {}},
  {"Aliased", 20, 0x0000, {}},
  {"Volatile", 21, 0x0000, {}},
  {"Constant", 22, 0x0040, {}},
  {"Coherent", 23, 0x0000, {}},
  {"NonWritable", 24, 0x0000, {}},
  {"NonReadable", 25, 0x0000, {}},
  {"Uniform", 26, 0x0002, {}},
  {"SaturatedConversion", 28, 0x0040, {}},
  {"Stream", 29, 0x40000000000000, {SPV_OPERAND_TYPE_LITERAL_INTEGER}},
  {"Location", 30, 0x0002, {SPV_OPERAND_TYPE_LITERAL_INTEGER}},
  {"Component", 31, 0x0002, {SPV_OPERAND_TYPE_LITERAL_INTEGER}},
  {"Index", 32, 0x0002, {SPV_OPERAND_TYPE_LITERAL_INTEGER}},
  {"Binding", 33, 0x0002, {SPV_OPERAND_TYPE_LITERAL_INTEGER}},
  {"DescriptorSet", 34, 0x0002, {SPV_OPERAND_TYPE_LITERAL_INTEGER}},
  {"Offset", 35, 0x0002, {SPV_OPERAND_TYPE_LITERAL_INTEGER}},
  {"XfbBuffer", 36, 0x20000000000000, {SPV_OPERAND_TYPE_LITERAL_INTEGER}},
  {"XfbStride", 37, 0x20000000000000, {SPV_OPERAND_TYPE_LITERAL_INTEGER}},
  {"FuncParamAttr", 38, 0x0040, {SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE}},
  {"FPRoundingMode", 39, 0x0040, {SPV_OPERAND_TYPE_FP_ROUNDING_MODE}},
  {"FPFastMathMode", 40, 0x0040, {SPV_OPERAND_TYPE_FP_FAST_MATH_MODE}},
  {"LinkageAttributes", 41, 0x0020, {SPV_OPERAND_TYPE_LITERAL_STRING, SPV_OPERAND_TYPE_LINKAGE_TYPE}},
  {"NoContraction", 42, 0x0002, {}},
  {"InputAttachmentIndex", 43, 0x10000000000, {SPV_OPERAND_TYPE_LITERAL_INTEGER}},
  {"Alignment", 44, 0x0040, {SPV_OPERAND_TYPE_LITERAL_INTEGER}}
};

static const spv_operand_desc_t pygen_variable_BuiltInEntries[] = {
  {"Position", 0, 0x0002, {}},
  {"PointSize", 1, 0x0002, {}},
  {"ClipDistance", 3, 0x100000000, {}},
  {"CullDistance", 4, 0x200000000, {}},
  {"VertexId", 5, 0x0002, {}},
  {"InstanceId", 6, 0x0002, {}},
  {"PrimitiveId", 7, 0x000c, {}},
  {"InvocationId", 8, 0x000c, {}},
  {"Layer", 9, 0x0004, {}},
  {"ViewportIndex", 10, 0x200000000000000, {}},
  {"TessLevelOuter", 11, 0x0008, {}},
  {"TessLevelInner", 12, 0x0008, {}},
  {"TessCoord", 13, 0x0008, {}},
  {"PatchVertices", 14, 0x0008, {}},
  {"FragCoord", 15, 0x0002, {}},
  {"PointCoord", 16, 0x0002, {}},
  {"FrontFacing", 17, 0x0002, {}},
  {"SampleId", 18, 0x800000000, {}},
  {"SamplePosition", 19, 0x800000000, {}},
  {"SampleMask", 20, 0x800000000, {}},
  {"FragDepth", 22, 0x0002, {}},
  {"HelperInvocation", 23, 0x0002, {}},
  {"NumWorkgroups", 24, 0x0000, {}},
  {"WorkgroupSize", 25, 0x0000, {}},
  {"WorkgroupId", 26, 0x0000, {}},
  {"LocalInvocationId", 27, 0x0000, {}},
  {"GlobalInvocationId", 28, 0x0000, {}},
  {"LocalInvocationIndex", 29, 0x0000, {}},
  {"WorkDim", 30, 0x0040, {}},
  {"GlobalSize", 31, 0x0040, {}},
  {"EnqueuedWorkgroupSize", 32, 0x0040, {}},
  {"GlobalOffset", 33, 0x0040, {}},
  {"GlobalLinearId", 34, 0x0040, {}},
  {"SubgroupSize", 36, 0x0040, {}},
  {"SubgroupMaxSize", 37, 0x0040, {}},
  {"NumSubgroups", 38, 0x0040, {}},
  {"NumEnqueuedSubgroups", 39, 0x0040, {}},
  {"SubgroupId", 40, 0x0040, {}},
  {"SubgroupLocalInvocationId", 41, 0x0040, {}},
  {"VertexIndex", 42, 0x0002, {}},
  {"InstanceIndex", 43, 0x0002, {}}
};

static const spv_operand_desc_t pygen_variable_ScopeEntries[] = {
  {"CrossDevice", 0, 0x0000, {}},
  {"Device", 1, 0x0000, {}},
  {"Workgroup", 2, 0x0000, {}},
  {"Subgroup", 3, 0x0000, {}},
  {"Invocation", 4, 0x0000, {}}
};

static const spv_operand_desc_t pygen_variable_GroupOperationEntries[] = {
  {"Reduce", 0, 0x0040, {}},
  {"InclusiveScan", 1, 0x0040, {}},
  {"ExclusiveScan", 2, 0x0040, {}}
};

static const spv_operand_desc_t pygen_variable_KernelEnqueueFlagsEntries[] = {
  {"NoWait", 0, 0x0040, {}},
  {"WaitKernel", 1, 0x0040, {}},
  {"WaitWorkGroup", 2, 0x0040, {}}
};

static const spv_operand_desc_t pygen_variable_CapabilityEntries[] = {
  {"Matrix", 0, 0x0000, {}},
  {"Shader", 1, 0x0001, {}},
  {"Geometry", 2, 0x0002, {}},
  {"Tessellation", 3, 0x0002, {}},
  {"Addresses", 4, 0x0000, {}},
  {"Linkage", 5, 0x0000, {}},
  {"Kernel", 6, 0x0000, {}},
  {"Vector16", 7, 0x0040, {}},
  {"Float16Buffer", 8, 0x0040, {}},
  {"Float16", 9, 0x0000, {}},
  {"Float64", 10, 0x0000, {}},
  {"Int64", 11, 0x0000, {}},
  {"Int64Atomics", 12, 0x0800, {}},
  {"ImageBasic", 13, 0x0040, {}},
  {"ImageReadWrite", 14, 0x2000, {}},
  {"ImageMipmap", 15, 0x2000, {}},
  {"Pipes", 17, 0x0040, {}},
  {"Groups", 18, 0x0000, {}},
  {"DeviceEnqueue", 19, 0x0040, {}},
  {"LiteralSampler", 20, 0x0040, {}},
  {"AtomicStorage", 21, 0x0002, {}},
  {"Int16", 22, 0x0000, {}},
  {"TessellationPointSize", 23, 0x0008, {}},
  {"GeometryPointSize", 24, 0x0004, {}},
  {"ImageGatherExtended", 25, 0x0002, {}},
  {"StorageImageMultisample", 27, 0x0002, {}},
  {"UniformBufferArrayDynamicIndexing", 28, 0x0002, {}},
  {"SampledImageArrayDynamicIndexing", 29, 0x0002, {}},
  {"StorageBufferArrayDynamicIndexing", 30, 0x0002, {}},
  {"StorageImageArrayDynamicIndexing", 31, 0x0002, {}},
  {"ClipDistance", 32, 0x0002, {}},
  {"CullDistance", 33, 0x0002, {}},
  {"ImageCubeArray", 34, 0x200000000000, {}},
  {"SampleRateShading", 35, 0x0002, {}},
  {"ImageRect", 36, 0x2000000000, {}},
  {"SampledRect", 37, 0x0002, {}},
  {"GenericPointer", 38, 0x0010, {}},
  {"Int8", 39, 0x0040, {}},
  {"InputAttachment", 40, 0x0002, {}},
  {"SparseResidency", 41, 0x0002, {}},
  {"MinLod", 42, 0x0002, {}},
  {"Sampled1D", 43, 0x0002, {}},
  {"Image1D", 44, 0x80000000000, {}},
  {"SampledCubeArray", 45, 0x0002, {}},
  {"SampledBuffer", 46, 0x0002, {}},
  {"ImageBuffer", 47, 0x400000000000, {}},
  {"ImageMSArray", 48, 0x0002, {}},
  {"StorageImageExtendedFormats", 49, 0x0002, {}},
  {"ImageQuery", 50, 0x0002, {}},
  {"DerivativeControl", 51, 0x0002, {}},
  {"InterpolationFunction", 52, 0x0002, {}},
  {"TransformFeedback", 53, 0x0002, {}},
  {"GeometryStreams", 54, 0x0004, {}},
  {"StorageImageReadWithoutFormat", 55, 0x0002, {}},
  {"StorageImageWriteWithoutFormat", 56, 0x0002, {}},
  {"MultiViewport", 57, 0x0004, {}}
};

static const spv_operand_desc_group_t pygen_variable_OperandInfoTable[] = {
  {SPV_OPERAND_TYPE_IMAGE, ARRAY_SIZE(pygen_variable_ImageOperandsEntries), pygen_variable_ImageOperandsEntries},
  {SPV_OPERAND_TYPE_FP_FAST_MATH_MODE, ARRAY_SIZE(pygen_variable_FPFastMathModeEntries), pygen_variable_FPFastMathModeEntries},
  {SPV_OPERAND_TYPE_SELECTION_CONTROL, ARRAY_SIZE(pygen_variable_SelectionControlEntries), pygen_variable_SelectionControlEntries},
  {SPV_OPERAND_TYPE_LOOP_CONTROL, ARRAY_SIZE(pygen_variable_LoopControlEntries), pygen_variable_LoopControlEntries},
  {SPV_OPERAND_TYPE_FUNCTION_CONTROL, ARRAY_SIZE(pygen_variable_FunctionControlEntries), pygen_variable_FunctionControlEntries},
  {SPV_OPERAND_TYPE_MEMORY_SEMANTICS_ID, ARRAY_SIZE(pygen_variable_MemorySemanticsEntries), pygen_variable_MemorySemanticsEntries},
  {SPV_OPERAND_TYPE_MEMORY_ACCESS, ARRAY_SIZE(pygen_variable_MemoryAccessEntries), pygen_variable_MemoryAccessEntries},
  {SPV_OPERAND_TYPE_KERNEL_PROFILING_INFO, ARRAY_SIZE(pygen_variable_KernelProfilingInfoEntries), pygen_variable_KernelProfilingInfoEntries},
  {SPV_OPERAND_TYPE_SOURCE_LANGUAGE, ARRAY_SIZE(pygen_variable_SourceLanguageEntries), pygen_variable_SourceLanguageEntries},
  {SPV_OPERAND_TYPE_EXECUTION_MODEL, ARRAY_SIZE(pygen_variable_ExecutionModelEntries), pygen_variable_ExecutionModelEntries},
  {SPV_OPERAND_TYPE_ADDRESSING_MODEL, ARRAY_SIZE(pygen_variable_AddressingModelEntries), pygen_variable_AddressingModelEntries},
  {SPV_OPERAND_TYPE_MEMORY_MODEL, ARRAY_SIZE(pygen_variable_MemoryModelEntries), pygen_variable_MemoryModelEntries},
  {SPV_OPERAND_TYPE_EXECUTION_MODE, ARRAY_SIZE(pygen_variable_ExecutionModeEntries), pygen_variable_ExecutionModeEntries},
  {SPV_OPERAND_TYPE_STORAGE_CLASS, ARRAY_SIZE(pygen_variable_StorageClassEntries), pygen_variable_StorageClassEntries},
  {SPV_OPERAND_TYPE_DIMENSIONALITY, ARRAY_SIZE(pygen_variable_DimEntries), pygen_variable_DimEntries},
  {SPV_OPERAND_TYPE_SAMPLER_ADDRESSING_MODE, ARRAY_SIZE(pygen_variable_SamplerAddressingModeEntries), pygen_variable_SamplerAddressingModeEntries},
  {SPV_OPERAND_TYPE_SAMPLER_FILTER_MODE, ARRAY_SIZE(pygen_variable_SamplerFilterModeEntries), pygen_variable_SamplerFilterModeEntries},
  {SPV_OPERAND_TYPE_SAMPLER_IMAGE_FORMAT, ARRAY_SIZE(pygen_variable_ImageFormatEntries), pygen_variable_ImageFormatEntries},
  {SPV_OPERAND_TYPE_IMAGE_CHANNEL_ORDER, ARRAY_SIZE(pygen_variable_ImageChannelOrderEntries), pygen_variable_ImageChannelOrderEntries},
  {SPV_OPERAND_TYPE_IMAGE_CHANNEL_DATA_TYPE, ARRAY_SIZE(pygen_variable_ImageChannelDataTypeEntries), pygen_variable_ImageChannelDataTypeEntries},
  {SPV_OPERAND_TYPE_FP_ROUNDING_MODE, ARRAY_SIZE(pygen_variable_FPRoundingModeEntries), pygen_variable_FPRoundingModeEntries},
  {SPV_OPERAND_TYPE_LINKAGE_TYPE, ARRAY_SIZE(pygen_variable_LinkageTypeEntries), pygen_variable_LinkageTypeEntries},
  {SPV_OPERAND_TYPE_ACCESS_QUALIFIER, ARRAY_SIZE(pygen_variable_AccessQualifierEntries), pygen_variable_AccessQualifierEntries},
  {SPV_OPERAND_TYPE_FUNCTION_PARAMETER_ATTRIBUTE, ARRAY_SIZE(pygen_variable_FunctionParameterAttributeEntries), pygen_variable_FunctionParameterAttributeEntries},
  {SPV_OPERAND_TYPE_DECORATION, ARRAY_SIZE(pygen_variable_DecorationEntries), pygen_variable_DecorationEntries},
  {SPV_OPERAND_TYPE_BUILT_IN, ARRAY_SIZE(pygen_variable_BuiltInEntries), pygen_variable_BuiltInEntries},
  {SPV_OPERAND_TYPE_SCOPE_ID, ARRAY_SIZE(pygen_variable_ScopeEntries), pygen_variable_ScopeEntries},
  {SPV_OPERAND_TYPE_GROUP_OPERATION, ARRAY_SIZE(pygen_variable_GroupOperationEntries), pygen_variable_GroupOperationEntries},
  {SPV_OPERAND_TYPE_KERNEL_ENQ_FLAGS, ARRAY_SIZE(pygen_variable_KernelEnqueueFlagsEntries), pygen_variable_KernelEnqueueFlagsEntries},
  {SPV_OPERAND_TYPE_CAPABILITY, ARRAY_SIZE(pygen_variable_CapabilityEntries), pygen_variable_CapabilityEntries},
  {SPV_OPERAND_TYPE_OPTIONAL_IMAGE, ARRAY_SIZE(pygen_variable_ImageOperandsEntries), pygen_variable_ImageOperandsEntries},
  {SPV_OPERAND_TYPE_OPTIONAL_MEMORY_ACCESS, ARRAY_SIZE(pygen_variable_MemoryAccessEntries), pygen_variable_MemoryAccessEntries},
  {SPV_OPERAND_TYPE_OPTIONAL_ACCESS_QUALIFIER, ARRAY_SIZE(pygen_variable_AccessQualifierEntries), pygen_variable_AccessQualifierEntries}
};
