// Copyright (c) 2015-2016 The Khronos Group Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and/or associated documentation files (the
// "Materials"), to deal in the Materials without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Materials, and to
// permit persons to whom the Materials are furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Materials.
//
// MODIFICATIONS TO THIS FILE MAY MEAN IT NO LONGER ACCURATELY REFLECTS
// KHRONOS STANDARDS. THE UNMODIFIED, NORMATIVE VERSIONS OF KHRONOS
// SPECIFICATIONS AND HEADER INFORMATION ARE LOCATED AT
//    https://www.khronos.org/registry/
//
// THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.

#ifndef LIBSPIRV_VAL_FUNCTION_H_
#define LIBSPIRV_VAL_FUNCTION_H_

#include <list>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "spirv/1.1/spirv.h"
#include "spirv-tools/libspirv.h"
#include "val/BasicBlock.h"

namespace libspirv {

enum class FunctionDecl {
  kFunctionDeclUnknown,      /// < Unknown function declaration
  kFunctionDeclDeclaration,  /// < Function declaration
  kFunctionDeclDefinition    /// < Function definition
};

class Construct;
class ValidationState_t;

/// This class manages all function declaration and definitions in a module. It
/// handles the state and id information while parsing a function in the SPIR-V
/// binary.
class Function {
 public:
  Function(uint32_t id, uint32_t result_type_id,
           SpvFunctionControlMask function_control, uint32_t function_type_id,
           ValidationState_t& module);

  /// Registers a function parameter in the current function
  /// @return Returns SPV_SUCCESS if the call was successful
  spv_result_t RegisterFunctionParameter(uint32_t id, uint32_t type_id);

  /// Sets the declaration type of the current function
  /// @return Returns SPV_SUCCESS if the call was successful
  spv_result_t RegisterSetFunctionDeclType(FunctionDecl type);

  /// Registers a block in the current function. Subsequent block instructions
  /// will target this block
  /// @param id The ID of the label of the block
  /// @return Returns SPV_SUCCESS if the call was successful
  spv_result_t RegisterBlock(uint32_t id, bool is_definition = true);

  /// Registers a variable in the current block
  ///
  /// @param[in] type_id The type ID of the varaible
  /// @param[in] id      The ID of the varaible
  /// @param[in] storage The storage of the variable
  /// @param[in] init_id The initializer ID of the variable
  ///
  /// @return Returns SPV_SUCCESS if the call was successful
  spv_result_t RegisterBlockVariable(uint32_t type_id, uint32_t id,
                                     SpvStorageClass storage, uint32_t init_id);

  /// Registers a loop merge construct in the function
  ///
  /// @param[in] merge_id The merge block ID of the loop
  /// @param[in] continue_id The continue block ID of the loop
  ///
  /// @return Returns SPV_SUCCESS if the call was successful
  spv_result_t RegisterLoopMerge(uint32_t merge_id, uint32_t continue_id);

  /// Registers a selection merge construct in the function
  /// @return Returns SPV_SUCCESS if the call was successful
  spv_result_t RegisterSelectionMerge(uint32_t merge_id);

  /// Registers the end of the block
  ///
  /// @param[in] successors_list A list of ids to the blocks successors
  /// @param[in] branch_instruction the branch instruction that ended the block
  void RegisterBlockEnd(std::vector<uint32_t> successors_list,
                        SpvOp branch_instruction);

  /// Returns true if the \p merge_block_id is a merge block
  bool IsMergeBlock(uint32_t merge_block_id) const;

  /// Returns true if the \p id is the first block of this function
  bool IsFirstBlock(uint32_t id) const;

  /// Returns the first block of the current function
  const BasicBlock* get_first_block() const;

  /// Returns the first block of the current function
  BasicBlock* get_first_block();

  /// Returns a vector of all the blocks in the function
  const std::vector<BasicBlock*>& get_blocks() const;

  /// Returns a vector of all the blocks in the function
  std::vector<BasicBlock*>& get_blocks();

  /// Returns a list of all the cfg constructs in the function
  const std::list<Construct>& get_constructs() const;

  /// Returns a list of all the cfg constructs in the function
  std::list<Construct>& get_constructs();

  /// Returns the number of blocks in the current function being parsed
  size_t get_block_count() const;

  /// Returns the id of the funciton
  uint32_t get_id() const { return id_; }

  /// Returns the number of blocks in the current function being parsed
  size_t get_undefined_block_count() const;
  const std::unordered_set<uint32_t>& get_undefined_blocks() const {
    return undefined_blocks_;
  }

  /// Returns the block that is currently being parsed in the binary
  BasicBlock* get_current_block();

  /// Returns the block that is currently being parsed in the binary
  const BasicBlock* get_current_block() const;

  /// Prints a GraphViz digraph of the CFG of the current funciton
  void printDotGraph() const;

  /// Prints a directed graph of the CFG of the current funciton
  void printBlocks() const;

 private:
  /// Parent module
  ValidationState_t& module_;

  /// The result id of the OpLabel that defined this block
  uint32_t id_;

  /// The type of the function
  uint32_t function_type_id_;

  /// The type of the return value
  uint32_t result_type_id_;

  /// The control fo the funciton
  SpvFunctionControlMask function_control_;

  /// The type of declaration of each function
  FunctionDecl declaration_type_;

  /// The blocks in the function mapped by block ID
  std::unordered_map<uint32_t, BasicBlock> blocks_;

  /// A list of blocks in the order they appeared in the binary
  std::vector<BasicBlock*> ordered_blocks_;

  /// Blocks which are forward referenced by blocks but not defined
  std::unordered_set<uint32_t> undefined_blocks_;

  /// The block that is currently being parsed
  BasicBlock* current_block_;

  /// The constructs that are available in this function
  std::list<Construct> cfg_constructs_;

  /// The variable IDs of the functions
  std::vector<uint32_t> variable_ids_;

  /// The function parameter ids of the functions
  std::vector<uint32_t> parameter_ids_;
};

}  /// namespace libspirv


#endif  /// LIBSPIRV_VAL_FUNCTION_H_
