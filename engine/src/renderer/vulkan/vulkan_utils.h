#pragma once
#include "vulkan_types.inl"

/**
 * Returns the string representation of result.
 * @param result.The result to get the string for.
 * @param get_extended Indicates wheter to also return the extended result.
 * @returns The error code and/or extended error message in string form. Defaults to success for unknown types.
 */
const char* vulkan_result_string(VkResult result, b8 get_extended);

/**
 * Indicates if the passed result is a success or an error as defined by the Vulkan spec.
 * @returns True if success; otherwis false. Defaults to true for unknown result type.
 */
b8 vulkan_result_is_success(VkResult result);
