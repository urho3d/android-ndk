/*
** Copyright (c) 2015 The Khronos Group Inc.
**
** Permission is hereby granted, free of charge, to any person obtaining a
** copy of this software and/or associated documentation files (the
** "Materials"), to deal in the Materials without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Materials, and to
** permit persons to whom the Materials are furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be included
** in all copies or substantial portions of the Materials.
**
** THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
** TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
** MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.
*/

/*
** This header is generated from the Khronos Vulkan XML API Registry.
**
*/

#ifndef PARAMETER_VALIDATION_H
#define PARAMETER_VALIDATION_H 1

#include "vulkan/vulkan.h"
#include "vk_layer_extension_utils.h"
#include "parameter_validation_utils.h"

#ifndef UNUSED_PARAMETER
#define UNUSED_PARAMETER(x) (void)(x)
#endif // UNUSED_PARAMETER

static VkBool32 parameter_validation_VkApplicationInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkApplicationInfo*                     pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkInstanceCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkInstanceCreateInfo*                  pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_type(report_data, pFuncName, (std::string(pVariableName) + std::string("pApplicationInfo")).c_str(), "VK_STRUCTURE_TYPE_APPLICATION_INFO", pStruct->pApplicationInfo, VK_STRUCTURE_TYPE_APPLICATION_INFO, VK_FALSE);

        skipCall |= validate_string_array(report_data, pFuncName, "enabledLayerCount", (std::string(pVariableName) + std::string("ppEnabledLayerNames")).c_str(), pStruct->enabledLayerCount, pStruct->ppEnabledLayerNames, VK_FALSE, VK_TRUE);

        skipCall |= validate_string_array(report_data, pFuncName, "enabledExtensionCount", (std::string(pVariableName) + std::string("ppEnabledExtensionNames")).c_str(), pStruct->enabledExtensionCount, pStruct->ppEnabledExtensionNames, VK_FALSE, VK_TRUE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkAllocationCallbacks(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkAllocationCallbacks*                 pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_required_pointer(report_data, pFuncName, (std::string(pVariableName) + std::string("pfnAllocation")).c_str(), reinterpret_cast<const void*>(pStruct->pfnAllocation));

        skipCall |= validate_required_pointer(report_data, pFuncName, (std::string(pVariableName) + std::string("pfnReallocation")).c_str(), reinterpret_cast<const void*>(pStruct->pfnReallocation));

        skipCall |= validate_required_pointer(report_data, pFuncName, (std::string(pVariableName) + std::string("pfnFree")).c_str(), reinterpret_cast<const void*>(pStruct->pfnFree));
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkDeviceQueueCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkDeviceQueueCreateInfo*               pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_array(report_data, pFuncName, "queueCount", (std::string(pVariableName) + std::string("pQueuePriorities")).c_str(), pStruct->queueCount, pStruct->pQueuePriorities, VK_TRUE, VK_TRUE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkDeviceCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkDeviceCreateInfo*                    pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_type_array(report_data, pFuncName, "queueCreateInfoCount", (std::string(pVariableName) + std::string("pQueueCreateInfos")).c_str(), "VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO", pStruct->queueCreateInfoCount, pStruct->pQueueCreateInfos, VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO, VK_TRUE, VK_TRUE);

        skipCall |= parameter_validation_VkDeviceQueueCreateInfo(report_data, pFuncName, (std::string(pVariableName) + std::string("pQueueCreateInfos->")).c_str(), pStruct->pQueueCreateInfos);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkSubmitInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkSubmitInfo*                          pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_array(report_data, pFuncName, "waitSemaphoreCount", (std::string(pVariableName) + std::string("pWaitSemaphores")).c_str(), pStruct->waitSemaphoreCount, pStruct->pWaitSemaphores, VK_FALSE, VK_TRUE);

        skipCall |= validate_array(report_data, pFuncName, "waitSemaphoreCount", (std::string(pVariableName) + std::string("pWaitDstStageMask")).c_str(), pStruct->waitSemaphoreCount, pStruct->pWaitDstStageMask, VK_FALSE, VK_TRUE);

        skipCall |= validate_array(report_data, pFuncName, "commandBufferCount", (std::string(pVariableName) + std::string("pCommandBuffers")).c_str(), pStruct->commandBufferCount, pStruct->pCommandBuffers, VK_FALSE, VK_TRUE);

        skipCall |= validate_array(report_data, pFuncName, "signalSemaphoreCount", (std::string(pVariableName) + std::string("pSignalSemaphores")).c_str(), pStruct->signalSemaphoreCount, pStruct->pSignalSemaphores, VK_FALSE, VK_TRUE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkMemoryAllocateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkMemoryAllocateInfo*                  pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkMappedMemoryRange(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkMappedMemoryRange*                   pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkSparseBufferMemoryBindInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkSparseBufferMemoryBindInfo*          pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_array(report_data, pFuncName, "bindCount", (std::string(pVariableName) + std::string("pBinds")).c_str(), pStruct->bindCount, pStruct->pBinds, VK_TRUE, VK_TRUE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkSparseImageOpaqueMemoryBindInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkSparseImageOpaqueMemoryBindInfo*     pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_array(report_data, pFuncName, "bindCount", (std::string(pVariableName) + std::string("pBinds")).c_str(), pStruct->bindCount, pStruct->pBinds, VK_TRUE, VK_TRUE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkSparseImageMemoryBindInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkSparseImageMemoryBindInfo*           pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_array(report_data, pFuncName, "bindCount", (std::string(pVariableName) + std::string("pBinds")).c_str(), pStruct->bindCount, pStruct->pBinds, VK_TRUE, VK_TRUE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkBindSparseInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkBindSparseInfo*                      pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_array(report_data, pFuncName, "waitSemaphoreCount", (std::string(pVariableName) + std::string("pWaitSemaphores")).c_str(), pStruct->waitSemaphoreCount, pStruct->pWaitSemaphores, VK_FALSE, VK_TRUE);

        skipCall |= validate_array(report_data, pFuncName, "bufferBindCount", (std::string(pVariableName) + std::string("pBufferBinds")).c_str(), pStruct->bufferBindCount, pStruct->pBufferBinds, VK_FALSE, VK_TRUE);

        skipCall |= parameter_validation_VkSparseBufferMemoryBindInfo(report_data, pFuncName, (std::string(pVariableName) + std::string("pBufferBinds->")).c_str(), pStruct->pBufferBinds);

        skipCall |= validate_array(report_data, pFuncName, "imageOpaqueBindCount", (std::string(pVariableName) + std::string("pImageOpaqueBinds")).c_str(), pStruct->imageOpaqueBindCount, pStruct->pImageOpaqueBinds, VK_FALSE, VK_TRUE);

        skipCall |= parameter_validation_VkSparseImageOpaqueMemoryBindInfo(report_data, pFuncName, (std::string(pVariableName) + std::string("pImageOpaqueBinds->")).c_str(), pStruct->pImageOpaqueBinds);

        skipCall |= validate_array(report_data, pFuncName, "imageBindCount", (std::string(pVariableName) + std::string("pImageBinds")).c_str(), pStruct->imageBindCount, pStruct->pImageBinds, VK_FALSE, VK_TRUE);

        skipCall |= parameter_validation_VkSparseImageMemoryBindInfo(report_data, pFuncName, (std::string(pVariableName) + std::string("pImageBinds->")).c_str(), pStruct->pImageBinds);

        skipCall |= validate_array(report_data, pFuncName, "signalSemaphoreCount", (std::string(pVariableName) + std::string("pSignalSemaphores")).c_str(), pStruct->signalSemaphoreCount, pStruct->pSignalSemaphores, VK_FALSE, VK_TRUE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkFenceCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkFenceCreateInfo*                     pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkSemaphoreCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkSemaphoreCreateInfo*                 pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkEventCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkEventCreateInfo*                     pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkQueryPoolCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkQueryPoolCreateInfo*                 pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkBufferCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkBufferCreateInfo*                    pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_array(report_data, pFuncName, "queueFamilyIndexCount", (std::string(pVariableName) + std::string("pQueueFamilyIndices")).c_str(), pStruct->queueFamilyIndexCount, pStruct->pQueueFamilyIndices, VK_FALSE, VK_TRUE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkBufferViewCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkBufferViewCreateInfo*                pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkImageCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkImageCreateInfo*                     pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_array(report_data, pFuncName, "queueFamilyIndexCount", (std::string(pVariableName) + std::string("pQueueFamilyIndices")).c_str(), pStruct->queueFamilyIndexCount, pStruct->pQueueFamilyIndices, VK_FALSE, VK_TRUE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkImageViewCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkImageViewCreateInfo*                 pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkShaderModuleCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkShaderModuleCreateInfo*              pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_array(report_data, pFuncName, "codeSize", (std::string(pVariableName) + std::string("pCode")).c_str(), pStruct->codeSize, pStruct->pCode, VK_TRUE, VK_TRUE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkPipelineCacheCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkPipelineCacheCreateInfo*             pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_array(report_data, pFuncName, "initialDataSize", (std::string(pVariableName) + std::string("pInitialData")).c_str(), pStruct->initialDataSize, pStruct->pInitialData, VK_FALSE, VK_TRUE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkSpecializationInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkSpecializationInfo*                  pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_array(report_data, pFuncName, "mapEntryCount", (std::string(pVariableName) + std::string("pMapEntries")).c_str(), pStruct->mapEntryCount, pStruct->pMapEntries, VK_FALSE, VK_TRUE);

        skipCall |= validate_array(report_data, pFuncName, "dataSize", (std::string(pVariableName) + std::string("pData")).c_str(), pStruct->dataSize, pStruct->pData, VK_FALSE, VK_TRUE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkPipelineShaderStageCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkPipelineShaderStageCreateInfo*       pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_required_pointer(report_data, pFuncName, (std::string(pVariableName) + std::string("pName")).c_str(), pStruct->pName);

        skipCall |= parameter_validation_VkSpecializationInfo(report_data, pFuncName, (std::string(pVariableName) + std::string("pSpecializationInfo->")).c_str(), pStruct->pSpecializationInfo);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkPipelineVertexInputStateCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkPipelineVertexInputStateCreateInfo*  pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_array(report_data, pFuncName, "vertexBindingDescriptionCount", (std::string(pVariableName) + std::string("pVertexBindingDescriptions")).c_str(), pStruct->vertexBindingDescriptionCount, pStruct->pVertexBindingDescriptions, VK_FALSE, VK_TRUE);

        skipCall |= validate_array(report_data, pFuncName, "vertexAttributeDescriptionCount", (std::string(pVariableName) + std::string("pVertexAttributeDescriptions")).c_str(), pStruct->vertexAttributeDescriptionCount, pStruct->pVertexAttributeDescriptions, VK_FALSE, VK_TRUE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkPipelineInputAssemblyStateCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkPipelineInputAssemblyStateCreateInfo* pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkPipelineTessellationStateCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkPipelineTessellationStateCreateInfo* pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkPipelineViewportStateCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkPipelineViewportStateCreateInfo*     pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_array(report_data, pFuncName, "viewportCount", (std::string(pVariableName) + std::string("pViewports")).c_str(), pStruct->viewportCount, pStruct->pViewports, VK_TRUE, VK_FALSE);

        skipCall |= validate_array(report_data, pFuncName, "scissorCount", (std::string(pVariableName) + std::string("pScissors")).c_str(), pStruct->scissorCount, pStruct->pScissors, VK_TRUE, VK_FALSE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkPipelineRasterizationStateCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkPipelineRasterizationStateCreateInfo* pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkPipelineMultisampleStateCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkPipelineMultisampleStateCreateInfo*  pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_array(report_data, pFuncName, "rasterizationSamples", (std::string(pVariableName) + std::string("pSampleMask")).c_str(), pStruct->rasterizationSamples, pStruct->pSampleMask, VK_TRUE, VK_FALSE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkPipelineDepthStencilStateCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkPipelineDepthStencilStateCreateInfo* pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkPipelineColorBlendStateCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkPipelineColorBlendStateCreateInfo*   pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_array(report_data, pFuncName, "attachmentCount", (std::string(pVariableName) + std::string("pAttachments")).c_str(), pStruct->attachmentCount, pStruct->pAttachments, VK_FALSE, VK_TRUE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkPipelineDynamicStateCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkPipelineDynamicStateCreateInfo*      pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_array(report_data, pFuncName, "dynamicStateCount", (std::string(pVariableName) + std::string("pDynamicStates")).c_str(), pStruct->dynamicStateCount, pStruct->pDynamicStates, VK_TRUE, VK_TRUE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkGraphicsPipelineCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkGraphicsPipelineCreateInfo*          pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_struct_type_array(report_data, pFuncName, "stageCount", (std::string(pVariableName) + std::string("pStages")).c_str(), "VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO", pStruct->stageCount, pStruct->pStages, VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO, VK_TRUE, VK_TRUE);

        skipCall |= parameter_validation_VkPipelineShaderStageCreateInfo(report_data, pFuncName, (std::string(pVariableName) + std::string("pStages->")).c_str(), pStruct->pStages);

        skipCall |= validate_struct_type(report_data, pFuncName, (std::string(pVariableName) + std::string("pVertexInputState")).c_str(), "VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO", pStruct->pVertexInputState, VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO, VK_TRUE);

        skipCall |= parameter_validation_VkPipelineVertexInputStateCreateInfo(report_data, pFuncName, (std::string(pVariableName) + std::string("pVertexInputState->")).c_str(), pStruct->pVertexInputState);

        skipCall |= validate_struct_type(report_data, pFuncName, (std::string(pVariableName) + std::string("pInputAssemblyState")).c_str(), "VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO", pStruct->pInputAssemblyState, VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO, VK_TRUE);

        skipCall |= validate_struct_type(report_data, pFuncName, (std::string(pVariableName) + std::string("pTessellationState")).c_str(), "VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO", pStruct->pTessellationState, VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO, VK_FALSE);

        skipCall |= validate_struct_type(report_data, pFuncName, (std::string(pVariableName) + std::string("pViewportState")).c_str(), "VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO", pStruct->pViewportState, VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO, VK_FALSE);

        skipCall |= parameter_validation_VkPipelineViewportStateCreateInfo(report_data, pFuncName, (std::string(pVariableName) + std::string("pViewportState->")).c_str(), pStruct->pViewportState);

        skipCall |= validate_struct_type(report_data, pFuncName, (std::string(pVariableName) + std::string("pRasterizationState")).c_str(), "VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO", pStruct->pRasterizationState, VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO, VK_TRUE);

        skipCall |= validate_struct_type(report_data, pFuncName, (std::string(pVariableName) + std::string("pMultisampleState")).c_str(), "VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO", pStruct->pMultisampleState, VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO, VK_FALSE);

        skipCall |= parameter_validation_VkPipelineMultisampleStateCreateInfo(report_data, pFuncName, (std::string(pVariableName) + std::string("pMultisampleState->")).c_str(), pStruct->pMultisampleState);

        skipCall |= validate_struct_type(report_data, pFuncName, (std::string(pVariableName) + std::string("pDepthStencilState")).c_str(), "VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO", pStruct->pDepthStencilState, VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO, VK_FALSE);

        skipCall |= validate_struct_type(report_data, pFuncName, (std::string(pVariableName) + std::string("pColorBlendState")).c_str(), "VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO", pStruct->pColorBlendState, VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO, VK_FALSE);

        skipCall |= parameter_validation_VkPipelineColorBlendStateCreateInfo(report_data, pFuncName, (std::string(pVariableName) + std::string("pColorBlendState->")).c_str(), pStruct->pColorBlendState);

        skipCall |= validate_struct_type(report_data, pFuncName, (std::string(pVariableName) + std::string("pDynamicState")).c_str(), "VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO", pStruct->pDynamicState, VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO, VK_FALSE);

        skipCall |= parameter_validation_VkPipelineDynamicStateCreateInfo(report_data, pFuncName, (std::string(pVariableName) + std::string("pDynamicState->")).c_str(), pStruct->pDynamicState);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkComputePipelineCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkComputePipelineCreateInfo*           pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= parameter_validation_VkPipelineShaderStageCreateInfo(report_data, pFuncName, (std::string(pVariableName) + std::string("stage.")).c_str(), &(pStruct->stage));
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkPipelineLayoutCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkPipelineLayoutCreateInfo*            pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_array(report_data, pFuncName, "setLayoutCount", (std::string(pVariableName) + std::string("pSetLayouts")).c_str(), pStruct->setLayoutCount, pStruct->pSetLayouts, VK_FALSE, VK_TRUE);

        skipCall |= validate_array(report_data, pFuncName, "pushConstantRangeCount", (std::string(pVariableName) + std::string("pPushConstantRanges")).c_str(), pStruct->pushConstantRangeCount, pStruct->pPushConstantRanges, VK_FALSE, VK_TRUE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkSamplerCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkSamplerCreateInfo*                   pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkDescriptorSetLayoutCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkDescriptorSetLayoutCreateInfo*       pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_array(report_data, pFuncName, "bindingCount", (std::string(pVariableName) + std::string("pBindings")).c_str(), pStruct->bindingCount, pStruct->pBindings, VK_FALSE, VK_TRUE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkDescriptorPoolCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkDescriptorPoolCreateInfo*            pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_array(report_data, pFuncName, "poolSizeCount", (std::string(pVariableName) + std::string("pPoolSizes")).c_str(), pStruct->poolSizeCount, pStruct->pPoolSizes, VK_TRUE, VK_TRUE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkDescriptorSetAllocateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkDescriptorSetAllocateInfo*           pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_array(report_data, pFuncName, "descriptorSetCount", (std::string(pVariableName) + std::string("pSetLayouts")).c_str(), pStruct->descriptorSetCount, pStruct->pSetLayouts, VK_TRUE, VK_TRUE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkWriteDescriptorSet(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkWriteDescriptorSet*                  pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_array(report_data, pFuncName, "descriptorCount", (std::string(pVariableName) + std::string("pImageInfo")).c_str(), pStruct->descriptorCount, pStruct->pImageInfo, VK_TRUE, VK_TRUE);

        skipCall |= validate_array(report_data, pFuncName, "descriptorCount", (std::string(pVariableName) + std::string("pBufferInfo")).c_str(), pStruct->descriptorCount, pStruct->pBufferInfo, VK_TRUE, VK_TRUE);

        skipCall |= validate_array(report_data, pFuncName, "descriptorCount", (std::string(pVariableName) + std::string("pTexelBufferView")).c_str(), pStruct->descriptorCount, pStruct->pTexelBufferView, VK_TRUE, VK_TRUE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkCopyDescriptorSet(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkCopyDescriptorSet*                   pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkFramebufferCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkFramebufferCreateInfo*               pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_array(report_data, pFuncName, "attachmentCount", (std::string(pVariableName) + std::string("pAttachments")).c_str(), pStruct->attachmentCount, pStruct->pAttachments, VK_FALSE, VK_TRUE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkSubpassDescription(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkSubpassDescription*                  pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_array(report_data, pFuncName, "inputAttachmentCount", (std::string(pVariableName) + std::string("pInputAttachments")).c_str(), pStruct->inputAttachmentCount, pStruct->pInputAttachments, VK_FALSE, VK_TRUE);

        skipCall |= validate_array(report_data, pFuncName, "colorAttachmentCount", (std::string(pVariableName) + std::string("pColorAttachments")).c_str(), pStruct->colorAttachmentCount, pStruct->pColorAttachments, VK_FALSE, VK_TRUE);

        skipCall |= validate_array(report_data, pFuncName, "preserveAttachmentCount", (std::string(pVariableName) + std::string("pPreserveAttachments")).c_str(), pStruct->preserveAttachmentCount, pStruct->pPreserveAttachments, VK_FALSE, VK_TRUE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkRenderPassCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkRenderPassCreateInfo*                pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_array(report_data, pFuncName, "attachmentCount", (std::string(pVariableName) + std::string("pAttachments")).c_str(), pStruct->attachmentCount, pStruct->pAttachments, VK_FALSE, VK_TRUE);

        skipCall |= validate_array(report_data, pFuncName, "subpassCount", (std::string(pVariableName) + std::string("pSubpasses")).c_str(), pStruct->subpassCount, pStruct->pSubpasses, VK_TRUE, VK_TRUE);

        skipCall |= parameter_validation_VkSubpassDescription(report_data, pFuncName, (std::string(pVariableName) + std::string("pSubpasses->")).c_str(), pStruct->pSubpasses);

        skipCall |= validate_array(report_data, pFuncName, "dependencyCount", (std::string(pVariableName) + std::string("pDependencies")).c_str(), pStruct->dependencyCount, pStruct->pDependencies, VK_FALSE, VK_TRUE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkCommandPoolCreateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkCommandPoolCreateInfo*               pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkCommandBufferAllocateInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkCommandBufferAllocateInfo*           pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkCommandBufferInheritanceInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkCommandBufferInheritanceInfo*        pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkCommandBufferBeginInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkCommandBufferBeginInfo*              pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_struct_type(report_data, pFuncName, (std::string(pVariableName) + std::string("pInheritanceInfo")).c_str(), "VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO", pStruct->pInheritanceInfo, VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO, VK_FALSE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkMemoryBarrier(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkMemoryBarrier*                       pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkBufferMemoryBarrier(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkBufferMemoryBarrier*                 pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkImageMemoryBarrier(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkImageMemoryBarrier*                  pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkRenderPassBeginInfo(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkRenderPassBeginInfo*                 pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_array(report_data, pFuncName, "clearValueCount", (std::string(pVariableName) + std::string("pClearValues")).c_str(), pStruct->clearValueCount, pStruct->pClearValues, VK_FALSE, VK_TRUE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_vkCreateInstance(
    debug_report_data*                          report_data,
    const VkInstanceCreateInfo*                 pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkInstance*                                 pInstance)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkCreateInstance", "pCreateInfo", "VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO", pCreateInfo, VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO, VK_TRUE);

    skipCall |= parameter_validation_VkInstanceCreateInfo(report_data, "vkCreateInstance", "pCreateInfo->", pCreateInfo);

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkCreateInstance", "pAllocator->", pAllocator);

    skipCall |= validate_required_pointer(report_data, "vkCreateInstance", "pInstance", pInstance);

    return skipCall;
}

static VkBool32 parameter_validation_vkDestroyInstance(
    debug_report_data*                          report_data,
    const VkAllocationCallbacks*                pAllocator)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkDestroyInstance", "pAllocator->", pAllocator);

    return skipCall;
}

static VkBool32 parameter_validation_vkEnumeratePhysicalDevices(
    debug_report_data*                          report_data,
    uint32_t*                                   pPhysicalDeviceCount,
    VkPhysicalDevice*                           pPhysicalDevices)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkEnumeratePhysicalDevices", "pPhysicalDeviceCount", "pPhysicalDevices", pPhysicalDeviceCount, pPhysicalDevices, VK_TRUE, VK_FALSE, VK_FALSE);

    return skipCall;
}

static VkBool32 parameter_validation_vkGetPhysicalDeviceFeatures(
    debug_report_data*                          report_data,
    VkPhysicalDeviceFeatures*                   pFeatures)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_required_pointer(report_data, "vkGetPhysicalDeviceFeatures", "pFeatures", pFeatures);

    return skipCall;
}

static VkBool32 parameter_validation_vkGetPhysicalDeviceFormatProperties(
    debug_report_data*                          report_data,
    VkFormat                                    format,
    VkFormatProperties*                         pFormatProperties)
{
    UNUSED_PARAMETER(format);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_required_pointer(report_data, "vkGetPhysicalDeviceFormatProperties", "pFormatProperties", pFormatProperties);

    return skipCall;
}

static VkBool32 parameter_validation_vkGetPhysicalDeviceImageFormatProperties(
    debug_report_data*                          report_data,
    VkFormat                                    format,
    VkImageType                                 type,
    VkImageTiling                               tiling,
    VkImageUsageFlags                           usage,
    VkImageCreateFlags                          flags,
    VkImageFormatProperties*                    pImageFormatProperties)
{
    UNUSED_PARAMETER(format);
    UNUSED_PARAMETER(type);
    UNUSED_PARAMETER(tiling);
    UNUSED_PARAMETER(usage);
    UNUSED_PARAMETER(flags);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_required_pointer(report_data, "vkGetPhysicalDeviceImageFormatProperties", "pImageFormatProperties", pImageFormatProperties);

    return skipCall;
}

static VkBool32 parameter_validation_vkGetPhysicalDeviceProperties(
    debug_report_data*                          report_data,
    VkPhysicalDeviceProperties*                 pProperties)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_required_pointer(report_data, "vkGetPhysicalDeviceProperties", "pProperties", pProperties);

    return skipCall;
}

static VkBool32 parameter_validation_vkGetPhysicalDeviceQueueFamilyProperties(
    debug_report_data*                          report_data,
    uint32_t*                                   pQueueFamilyPropertyCount,
    VkQueueFamilyProperties*                    pQueueFamilyProperties)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkGetPhysicalDeviceQueueFamilyProperties", "pQueueFamilyPropertyCount", "pQueueFamilyProperties", pQueueFamilyPropertyCount, pQueueFamilyProperties, VK_TRUE, VK_FALSE, VK_FALSE);

    return skipCall;
}

static VkBool32 parameter_validation_vkGetPhysicalDeviceMemoryProperties(
    debug_report_data*                          report_data,
    VkPhysicalDeviceMemoryProperties*           pMemoryProperties)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_required_pointer(report_data, "vkGetPhysicalDeviceMemoryProperties", "pMemoryProperties", pMemoryProperties);

    return skipCall;
}

static VkBool32 parameter_validation_vkCreateDevice(
    debug_report_data*                          report_data,
    const VkDeviceCreateInfo*                   pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkDevice*                                   pDevice)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkCreateDevice", "pCreateInfo", "VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO", pCreateInfo, VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO, VK_TRUE);

    skipCall |= parameter_validation_VkDeviceCreateInfo(report_data, "vkCreateDevice", "pCreateInfo->", pCreateInfo);

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkCreateDevice", "pAllocator->", pAllocator);

    skipCall |= validate_required_pointer(report_data, "vkCreateDevice", "pDevice", pDevice);

    return skipCall;
}

static VkBool32 parameter_validation_vkDestroyDevice(
    debug_report_data*                          report_data,
    const VkAllocationCallbacks*                pAllocator)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkDestroyDevice", "pAllocator->", pAllocator);

    return skipCall;
}

static VkBool32 parameter_validation_vkEnumerateInstanceExtensionProperties(
    debug_report_data*                          report_data,
    uint32_t*                                   pPropertyCount,
    VkExtensionProperties*                      pProperties)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkEnumerateInstanceExtensionProperties", "pPropertyCount", "pProperties", pPropertyCount, pProperties, VK_TRUE, VK_FALSE, VK_FALSE);

    return skipCall;
}

static VkBool32 parameter_validation_vkEnumerateDeviceExtensionProperties(
    debug_report_data*                          report_data,
    const char*                                 pLayerName,
    uint32_t*                                   pPropertyCount,
    VkExtensionProperties*                      pProperties)
{
    UNUSED_PARAMETER(pLayerName);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkEnumerateDeviceExtensionProperties", "pPropertyCount", "pProperties", pPropertyCount, pProperties, VK_TRUE, VK_FALSE, VK_FALSE);

    return skipCall;
}

static VkBool32 parameter_validation_vkGetDeviceQueue(
    debug_report_data*                          report_data,
    uint32_t                                    queueFamilyIndex,
    uint32_t                                    queueIndex,
    VkQueue*                                    pQueue)
{
    UNUSED_PARAMETER(queueFamilyIndex);
    UNUSED_PARAMETER(queueIndex);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_required_pointer(report_data, "vkGetDeviceQueue", "pQueue", pQueue);

    return skipCall;
}

static VkBool32 parameter_validation_vkQueueSubmit(
    debug_report_data*                          report_data,
    uint32_t                                    submitCount,
    const VkSubmitInfo*                         pSubmits,
    VkFence                                     fence)
{
    UNUSED_PARAMETER(fence);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type_array(report_data, "vkQueueSubmit", "submitCount", "pSubmits", "VK_STRUCTURE_TYPE_SUBMIT_INFO", submitCount, pSubmits, VK_STRUCTURE_TYPE_SUBMIT_INFO, VK_FALSE, VK_TRUE);

    skipCall |= parameter_validation_VkSubmitInfo(report_data, "vkQueueSubmit", "pSubmits->", pSubmits);

    return skipCall;
}

static VkBool32 parameter_validation_vkAllocateMemory(
    debug_report_data*                          report_data,
    const VkMemoryAllocateInfo*                 pAllocateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkDeviceMemory*                             pMemory)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkAllocateMemory", "pAllocateInfo", "VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO", pAllocateInfo, VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, VK_TRUE);

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkAllocateMemory", "pAllocator->", pAllocator);

    skipCall |= validate_required_pointer(report_data, "vkAllocateMemory", "pMemory", pMemory);

    return skipCall;
}

static VkBool32 parameter_validation_vkFreeMemory(
    debug_report_data*                          report_data,
    VkDeviceMemory                              memory,
    const VkAllocationCallbacks*                pAllocator)
{
    UNUSED_PARAMETER(memory);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkFreeMemory", "pAllocator->", pAllocator);

    return skipCall;
}

static VkBool32 parameter_validation_vkMapMemory(
    debug_report_data*                          report_data,
    VkDeviceMemory                              memory,
    VkDeviceSize                                offset,
    VkDeviceSize                                size,
    VkMemoryMapFlags                            flags,
    void**                                      ppData)
{
    UNUSED_PARAMETER(memory);
    UNUSED_PARAMETER(offset);
    UNUSED_PARAMETER(size);
    UNUSED_PARAMETER(flags);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_required_pointer(report_data, "vkMapMemory", "ppData", ppData);

    return skipCall;
}

static VkBool32 parameter_validation_vkFlushMappedMemoryRanges(
    debug_report_data*                          report_data,
    uint32_t                                    memoryRangeCount,
    const VkMappedMemoryRange*                  pMemoryRanges)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type_array(report_data, "vkFlushMappedMemoryRanges", "memoryRangeCount", "pMemoryRanges", "VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE", memoryRangeCount, pMemoryRanges, VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE, VK_TRUE, VK_TRUE);

    return skipCall;
}

static VkBool32 parameter_validation_vkInvalidateMappedMemoryRanges(
    debug_report_data*                          report_data,
    uint32_t                                    memoryRangeCount,
    const VkMappedMemoryRange*                  pMemoryRanges)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type_array(report_data, "vkInvalidateMappedMemoryRanges", "memoryRangeCount", "pMemoryRanges", "VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE", memoryRangeCount, pMemoryRanges, VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE, VK_TRUE, VK_TRUE);

    return skipCall;
}

static VkBool32 parameter_validation_vkGetDeviceMemoryCommitment(
    debug_report_data*                          report_data,
    VkDeviceMemory                              memory,
    VkDeviceSize*                               pCommittedMemoryInBytes)
{
    UNUSED_PARAMETER(memory);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_required_pointer(report_data, "vkGetDeviceMemoryCommitment", "pCommittedMemoryInBytes", pCommittedMemoryInBytes);

    return skipCall;
}

static VkBool32 parameter_validation_vkGetBufferMemoryRequirements(
    debug_report_data*                          report_data,
    VkBuffer                                    buffer,
    VkMemoryRequirements*                       pMemoryRequirements)
{
    UNUSED_PARAMETER(buffer);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_required_pointer(report_data, "vkGetBufferMemoryRequirements", "pMemoryRequirements", pMemoryRequirements);

    return skipCall;
}

static VkBool32 parameter_validation_vkGetImageMemoryRequirements(
    debug_report_data*                          report_data,
    VkImage                                     image,
    VkMemoryRequirements*                       pMemoryRequirements)
{
    UNUSED_PARAMETER(image);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_required_pointer(report_data, "vkGetImageMemoryRequirements", "pMemoryRequirements", pMemoryRequirements);

    return skipCall;
}

static VkBool32 parameter_validation_vkGetImageSparseMemoryRequirements(
    debug_report_data*                          report_data,
    VkImage                                     image,
    uint32_t*                                   pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements*            pSparseMemoryRequirements)
{
    UNUSED_PARAMETER(image);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkGetImageSparseMemoryRequirements", "pSparseMemoryRequirementCount", "pSparseMemoryRequirements", pSparseMemoryRequirementCount, pSparseMemoryRequirements, VK_TRUE, VK_TRUE, VK_FALSE);

    return skipCall;
}

static VkBool32 parameter_validation_vkGetPhysicalDeviceSparseImageFormatProperties(
    debug_report_data*                          report_data,
    VkFormat                                    format,
    VkImageType                                 type,
    VkSampleCountFlagBits                       samples,
    VkImageUsageFlags                           usage,
    VkImageTiling                               tiling,
    uint32_t*                                   pPropertyCount,
    VkSparseImageFormatProperties*              pProperties)
{
    UNUSED_PARAMETER(format);
    UNUSED_PARAMETER(type);
    UNUSED_PARAMETER(samples);
    UNUSED_PARAMETER(usage);
    UNUSED_PARAMETER(tiling);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkGetPhysicalDeviceSparseImageFormatProperties", "pPropertyCount", "pProperties", pPropertyCount, pProperties, VK_TRUE, VK_FALSE, VK_FALSE);

    return skipCall;
}

static VkBool32 parameter_validation_vkQueueBindSparse(
    debug_report_data*                          report_data,
    uint32_t                                    bindInfoCount,
    const VkBindSparseInfo*                     pBindInfo,
    VkFence                                     fence)
{
    UNUSED_PARAMETER(fence);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type_array(report_data, "vkQueueBindSparse", "bindInfoCount", "pBindInfo", "VK_STRUCTURE_TYPE_BIND_SPARSE_INFO", bindInfoCount, pBindInfo, VK_STRUCTURE_TYPE_BIND_SPARSE_INFO, VK_FALSE, VK_TRUE);

    skipCall |= parameter_validation_VkBindSparseInfo(report_data, "vkQueueBindSparse", "pBindInfo->", pBindInfo);

    return skipCall;
}

static VkBool32 parameter_validation_vkCreateFence(
    debug_report_data*                          report_data,
    const VkFenceCreateInfo*                    pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkFence*                                    pFence)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkCreateFence", "pCreateInfo", "VK_STRUCTURE_TYPE_FENCE_CREATE_INFO", pCreateInfo, VK_STRUCTURE_TYPE_FENCE_CREATE_INFO, VK_TRUE);

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkCreateFence", "pAllocator->", pAllocator);

    skipCall |= validate_required_pointer(report_data, "vkCreateFence", "pFence", pFence);

    return skipCall;
}

static VkBool32 parameter_validation_vkDestroyFence(
    debug_report_data*                          report_data,
    VkFence                                     fence,
    const VkAllocationCallbacks*                pAllocator)
{
    UNUSED_PARAMETER(fence);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkDestroyFence", "pAllocator->", pAllocator);

    return skipCall;
}

static VkBool32 parameter_validation_vkResetFences(
    debug_report_data*                          report_data,
    uint32_t                                    fenceCount,
    const VkFence*                              pFences)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkResetFences", "fenceCount", "pFences", fenceCount, pFences, VK_TRUE, VK_TRUE);

    return skipCall;
}

static VkBool32 parameter_validation_vkWaitForFences(
    debug_report_data*                          report_data,
    uint32_t                                    fenceCount,
    const VkFence*                              pFences,
    VkBool32                                    waitAll,
    uint64_t                                    timeout)
{
    UNUSED_PARAMETER(waitAll);
    UNUSED_PARAMETER(timeout);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkWaitForFences", "fenceCount", "pFences", fenceCount, pFences, VK_TRUE, VK_TRUE);

    return skipCall;
}

static VkBool32 parameter_validation_vkCreateSemaphore(
    debug_report_data*                          report_data,
    const VkSemaphoreCreateInfo*                pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSemaphore*                                pSemaphore)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkCreateSemaphore", "pCreateInfo", "VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO", pCreateInfo, VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO, VK_TRUE);

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkCreateSemaphore", "pAllocator->", pAllocator);

    skipCall |= validate_required_pointer(report_data, "vkCreateSemaphore", "pSemaphore", pSemaphore);

    return skipCall;
}

static VkBool32 parameter_validation_vkDestroySemaphore(
    debug_report_data*                          report_data,
    VkSemaphore                                 semaphore,
    const VkAllocationCallbacks*                pAllocator)
{
    UNUSED_PARAMETER(semaphore);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkDestroySemaphore", "pAllocator->", pAllocator);

    return skipCall;
}

static VkBool32 parameter_validation_vkCreateEvent(
    debug_report_data*                          report_data,
    const VkEventCreateInfo*                    pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkEvent*                                    pEvent)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkCreateEvent", "pCreateInfo", "VK_STRUCTURE_TYPE_EVENT_CREATE_INFO", pCreateInfo, VK_STRUCTURE_TYPE_EVENT_CREATE_INFO, VK_TRUE);

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkCreateEvent", "pAllocator->", pAllocator);

    skipCall |= validate_required_pointer(report_data, "vkCreateEvent", "pEvent", pEvent);

    return skipCall;
}

static VkBool32 parameter_validation_vkDestroyEvent(
    debug_report_data*                          report_data,
    VkEvent                                     event,
    const VkAllocationCallbacks*                pAllocator)
{
    UNUSED_PARAMETER(event);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkDestroyEvent", "pAllocator->", pAllocator);

    return skipCall;
}

static VkBool32 parameter_validation_vkCreateQueryPool(
    debug_report_data*                          report_data,
    const VkQueryPoolCreateInfo*                pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkQueryPool*                                pQueryPool)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkCreateQueryPool", "pCreateInfo", "VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO", pCreateInfo, VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO, VK_TRUE);

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkCreateQueryPool", "pAllocator->", pAllocator);

    skipCall |= validate_required_pointer(report_data, "vkCreateQueryPool", "pQueryPool", pQueryPool);

    return skipCall;
}

static VkBool32 parameter_validation_vkDestroyQueryPool(
    debug_report_data*                          report_data,
    VkQueryPool                                 queryPool,
    const VkAllocationCallbacks*                pAllocator)
{
    UNUSED_PARAMETER(queryPool);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkDestroyQueryPool", "pAllocator->", pAllocator);

    return skipCall;
}

static VkBool32 parameter_validation_vkGetQueryPoolResults(
    debug_report_data*                          report_data,
    VkQueryPool                                 queryPool,
    uint32_t                                    firstQuery,
    uint32_t                                    queryCount,
    size_t                                      dataSize,
    void*                                       pData,
    VkDeviceSize                                stride,
    VkQueryResultFlags                          flags)
{
    UNUSED_PARAMETER(queryPool);
    UNUSED_PARAMETER(firstQuery);
    UNUSED_PARAMETER(queryCount);
    UNUSED_PARAMETER(stride);
    UNUSED_PARAMETER(flags);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkGetQueryPoolResults", "dataSize", "pData", dataSize, pData, VK_TRUE, VK_TRUE);

    return skipCall;
}

static VkBool32 parameter_validation_vkCreateBuffer(
    debug_report_data*                          report_data,
    const VkBufferCreateInfo*                   pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkBuffer*                                   pBuffer)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkCreateBuffer", "pCreateInfo", "VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO", pCreateInfo, VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO, VK_TRUE);

    skipCall |= parameter_validation_VkBufferCreateInfo(report_data, "vkCreateBuffer", "pCreateInfo->", pCreateInfo);

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkCreateBuffer", "pAllocator->", pAllocator);

    skipCall |= validate_required_pointer(report_data, "vkCreateBuffer", "pBuffer", pBuffer);

    return skipCall;
}

static VkBool32 parameter_validation_vkDestroyBuffer(
    debug_report_data*                          report_data,
    VkBuffer                                    buffer,
    const VkAllocationCallbacks*                pAllocator)
{
    UNUSED_PARAMETER(buffer);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkDestroyBuffer", "pAllocator->", pAllocator);

    return skipCall;
}

static VkBool32 parameter_validation_vkCreateBufferView(
    debug_report_data*                          report_data,
    const VkBufferViewCreateInfo*               pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkBufferView*                               pView)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkCreateBufferView", "pCreateInfo", "VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO", pCreateInfo, VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO, VK_TRUE);

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkCreateBufferView", "pAllocator->", pAllocator);

    skipCall |= validate_required_pointer(report_data, "vkCreateBufferView", "pView", pView);

    return skipCall;
}

static VkBool32 parameter_validation_vkDestroyBufferView(
    debug_report_data*                          report_data,
    VkBufferView                                bufferView,
    const VkAllocationCallbacks*                pAllocator)
{
    UNUSED_PARAMETER(bufferView);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkDestroyBufferView", "pAllocator->", pAllocator);

    return skipCall;
}

static VkBool32 parameter_validation_vkCreateImage(
    debug_report_data*                          report_data,
    const VkImageCreateInfo*                    pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkImage*                                    pImage)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkCreateImage", "pCreateInfo", "VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO", pCreateInfo, VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO, VK_TRUE);

    skipCall |= parameter_validation_VkImageCreateInfo(report_data, "vkCreateImage", "pCreateInfo->", pCreateInfo);

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkCreateImage", "pAllocator->", pAllocator);

    skipCall |= validate_required_pointer(report_data, "vkCreateImage", "pImage", pImage);

    return skipCall;
}

static VkBool32 parameter_validation_vkDestroyImage(
    debug_report_data*                          report_data,
    VkImage                                     image,
    const VkAllocationCallbacks*                pAllocator)
{
    UNUSED_PARAMETER(image);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkDestroyImage", "pAllocator->", pAllocator);

    return skipCall;
}

static VkBool32 parameter_validation_vkGetImageSubresourceLayout(
    debug_report_data*                          report_data,
    VkImage                                     image,
    const VkImageSubresource*                   pSubresource,
    VkSubresourceLayout*                        pLayout)
{
    UNUSED_PARAMETER(image);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_required_pointer(report_data, "vkGetImageSubresourceLayout", "pSubresource", pSubresource);

    skipCall |= validate_required_pointer(report_data, "vkGetImageSubresourceLayout", "pLayout", pLayout);

    return skipCall;
}

static VkBool32 parameter_validation_vkCreateImageView(
    debug_report_data*                          report_data,
    const VkImageViewCreateInfo*                pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkImageView*                                pView)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkCreateImageView", "pCreateInfo", "VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO", pCreateInfo, VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO, VK_TRUE);

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkCreateImageView", "pAllocator->", pAllocator);

    skipCall |= validate_required_pointer(report_data, "vkCreateImageView", "pView", pView);

    return skipCall;
}

static VkBool32 parameter_validation_vkDestroyImageView(
    debug_report_data*                          report_data,
    VkImageView                                 imageView,
    const VkAllocationCallbacks*                pAllocator)
{
    UNUSED_PARAMETER(imageView);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkDestroyImageView", "pAllocator->", pAllocator);

    return skipCall;
}

static VkBool32 parameter_validation_vkCreateShaderModule(
    debug_report_data*                          report_data,
    const VkShaderModuleCreateInfo*             pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkShaderModule*                             pShaderModule)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkCreateShaderModule", "pCreateInfo", "VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO", pCreateInfo, VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO, VK_TRUE);

    skipCall |= parameter_validation_VkShaderModuleCreateInfo(report_data, "vkCreateShaderModule", "pCreateInfo->", pCreateInfo);

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkCreateShaderModule", "pAllocator->", pAllocator);

    skipCall |= validate_required_pointer(report_data, "vkCreateShaderModule", "pShaderModule", pShaderModule);

    return skipCall;
}

static VkBool32 parameter_validation_vkDestroyShaderModule(
    debug_report_data*                          report_data,
    VkShaderModule                              shaderModule,
    const VkAllocationCallbacks*                pAllocator)
{
    UNUSED_PARAMETER(shaderModule);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkDestroyShaderModule", "pAllocator->", pAllocator);

    return skipCall;
}

static VkBool32 parameter_validation_vkCreatePipelineCache(
    debug_report_data*                          report_data,
    const VkPipelineCacheCreateInfo*            pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkPipelineCache*                            pPipelineCache)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkCreatePipelineCache", "pCreateInfo", "VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO", pCreateInfo, VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO, VK_TRUE);

    skipCall |= parameter_validation_VkPipelineCacheCreateInfo(report_data, "vkCreatePipelineCache", "pCreateInfo->", pCreateInfo);

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkCreatePipelineCache", "pAllocator->", pAllocator);

    skipCall |= validate_required_pointer(report_data, "vkCreatePipelineCache", "pPipelineCache", pPipelineCache);

    return skipCall;
}

static VkBool32 parameter_validation_vkDestroyPipelineCache(
    debug_report_data*                          report_data,
    VkPipelineCache                             pipelineCache,
    const VkAllocationCallbacks*                pAllocator)
{
    UNUSED_PARAMETER(pipelineCache);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkDestroyPipelineCache", "pAllocator->", pAllocator);

    return skipCall;
}

static VkBool32 parameter_validation_vkGetPipelineCacheData(
    debug_report_data*                          report_data,
    VkPipelineCache                             pipelineCache,
    size_t*                                     pDataSize,
    void*                                       pData)
{
    UNUSED_PARAMETER(pipelineCache);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkGetPipelineCacheData", "pDataSize", "pData", pDataSize, pData, VK_TRUE, VK_FALSE, VK_FALSE);

    return skipCall;
}

static VkBool32 parameter_validation_vkMergePipelineCaches(
    debug_report_data*                          report_data,
    VkPipelineCache                             dstCache,
    uint32_t                                    srcCacheCount,
    const VkPipelineCache*                      pSrcCaches)
{
    UNUSED_PARAMETER(dstCache);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkMergePipelineCaches", "srcCacheCount", "pSrcCaches", srcCacheCount, pSrcCaches, VK_TRUE, VK_TRUE);

    return skipCall;
}

static VkBool32 parameter_validation_vkCreateGraphicsPipelines(
    debug_report_data*                          report_data,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    createInfoCount,
    const VkGraphicsPipelineCreateInfo*         pCreateInfos,
    const VkAllocationCallbacks*                pAllocator,
    VkPipeline*                                 pPipelines)
{
    UNUSED_PARAMETER(pipelineCache);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type_array(report_data, "vkCreateGraphicsPipelines", "createInfoCount", "pCreateInfos", "VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO", createInfoCount, pCreateInfos, VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO, VK_TRUE, VK_TRUE);

    skipCall |= parameter_validation_VkGraphicsPipelineCreateInfo(report_data, "vkCreateGraphicsPipelines", "pCreateInfos->", pCreateInfos);

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkCreateGraphicsPipelines", "pAllocator->", pAllocator);

    skipCall |= validate_array(report_data, "vkCreateGraphicsPipelines", "createInfoCount", "pPipelines", createInfoCount, pPipelines, VK_TRUE, VK_TRUE);

    return skipCall;
}

static VkBool32 parameter_validation_vkCreateComputePipelines(
    debug_report_data*                          report_data,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    createInfoCount,
    const VkComputePipelineCreateInfo*          pCreateInfos,
    const VkAllocationCallbacks*                pAllocator,
    VkPipeline*                                 pPipelines)
{
    UNUSED_PARAMETER(pipelineCache);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type_array(report_data, "vkCreateComputePipelines", "createInfoCount", "pCreateInfos", "VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO", createInfoCount, pCreateInfos, VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO, VK_TRUE, VK_TRUE);

    skipCall |= parameter_validation_VkComputePipelineCreateInfo(report_data, "vkCreateComputePipelines", "pCreateInfos->", pCreateInfos);

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkCreateComputePipelines", "pAllocator->", pAllocator);

    skipCall |= validate_array(report_data, "vkCreateComputePipelines", "createInfoCount", "pPipelines", createInfoCount, pPipelines, VK_TRUE, VK_TRUE);

    return skipCall;
}

static VkBool32 parameter_validation_vkDestroyPipeline(
    debug_report_data*                          report_data,
    VkPipeline                                  pipeline,
    const VkAllocationCallbacks*                pAllocator)
{
    UNUSED_PARAMETER(pipeline);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkDestroyPipeline", "pAllocator->", pAllocator);

    return skipCall;
}

static VkBool32 parameter_validation_vkCreatePipelineLayout(
    debug_report_data*                          report_data,
    const VkPipelineLayoutCreateInfo*           pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkPipelineLayout*                           pPipelineLayout)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkCreatePipelineLayout", "pCreateInfo", "VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO", pCreateInfo, VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO, VK_TRUE);

    skipCall |= parameter_validation_VkPipelineLayoutCreateInfo(report_data, "vkCreatePipelineLayout", "pCreateInfo->", pCreateInfo);

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkCreatePipelineLayout", "pAllocator->", pAllocator);

    skipCall |= validate_required_pointer(report_data, "vkCreatePipelineLayout", "pPipelineLayout", pPipelineLayout);

    return skipCall;
}

static VkBool32 parameter_validation_vkDestroyPipelineLayout(
    debug_report_data*                          report_data,
    VkPipelineLayout                            pipelineLayout,
    const VkAllocationCallbacks*                pAllocator)
{
    UNUSED_PARAMETER(pipelineLayout);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkDestroyPipelineLayout", "pAllocator->", pAllocator);

    return skipCall;
}

static VkBool32 parameter_validation_vkCreateSampler(
    debug_report_data*                          report_data,
    const VkSamplerCreateInfo*                  pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSampler*                                  pSampler)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkCreateSampler", "pCreateInfo", "VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO", pCreateInfo, VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO, VK_TRUE);

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkCreateSampler", "pAllocator->", pAllocator);

    skipCall |= validate_required_pointer(report_data, "vkCreateSampler", "pSampler", pSampler);

    return skipCall;
}

static VkBool32 parameter_validation_vkDestroySampler(
    debug_report_data*                          report_data,
    VkSampler                                   sampler,
    const VkAllocationCallbacks*                pAllocator)
{
    UNUSED_PARAMETER(sampler);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkDestroySampler", "pAllocator->", pAllocator);

    return skipCall;
}

static VkBool32 parameter_validation_vkCreateDescriptorSetLayout(
    debug_report_data*                          report_data,
    const VkDescriptorSetLayoutCreateInfo*      pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkDescriptorSetLayout*                      pSetLayout)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkCreateDescriptorSetLayout", "pCreateInfo", "VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO", pCreateInfo, VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO, VK_TRUE);

    skipCall |= parameter_validation_VkDescriptorSetLayoutCreateInfo(report_data, "vkCreateDescriptorSetLayout", "pCreateInfo->", pCreateInfo);

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkCreateDescriptorSetLayout", "pAllocator->", pAllocator);

    skipCall |= validate_required_pointer(report_data, "vkCreateDescriptorSetLayout", "pSetLayout", pSetLayout);

    return skipCall;
}

static VkBool32 parameter_validation_vkDestroyDescriptorSetLayout(
    debug_report_data*                          report_data,
    VkDescriptorSetLayout                       descriptorSetLayout,
    const VkAllocationCallbacks*                pAllocator)
{
    UNUSED_PARAMETER(descriptorSetLayout);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkDestroyDescriptorSetLayout", "pAllocator->", pAllocator);

    return skipCall;
}

static VkBool32 parameter_validation_vkCreateDescriptorPool(
    debug_report_data*                          report_data,
    const VkDescriptorPoolCreateInfo*           pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkDescriptorPool*                           pDescriptorPool)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkCreateDescriptorPool", "pCreateInfo", "VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO", pCreateInfo, VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO, VK_TRUE);

    skipCall |= parameter_validation_VkDescriptorPoolCreateInfo(report_data, "vkCreateDescriptorPool", "pCreateInfo->", pCreateInfo);

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkCreateDescriptorPool", "pAllocator->", pAllocator);

    skipCall |= validate_required_pointer(report_data, "vkCreateDescriptorPool", "pDescriptorPool", pDescriptorPool);

    return skipCall;
}

static VkBool32 parameter_validation_vkDestroyDescriptorPool(
    debug_report_data*                          report_data,
    VkDescriptorPool                            descriptorPool,
    const VkAllocationCallbacks*                pAllocator)
{
    UNUSED_PARAMETER(descriptorPool);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkDestroyDescriptorPool", "pAllocator->", pAllocator);

    return skipCall;
}

static VkBool32 parameter_validation_vkAllocateDescriptorSets(
    debug_report_data*                          report_data,
    const VkDescriptorSetAllocateInfo*          pAllocateInfo,
    VkDescriptorSet*                            pDescriptorSets)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkAllocateDescriptorSets", "pAllocateInfo", "VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO", pAllocateInfo, VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO, VK_TRUE);

    skipCall |= parameter_validation_VkDescriptorSetAllocateInfo(report_data, "vkAllocateDescriptorSets", "pAllocateInfo->", pAllocateInfo);

    if (pAllocateInfo != NULL) {
        skipCall |= validate_array(report_data, "vkAllocateDescriptorSets", "pAllocateInfo->descriptorSetCount", "pDescriptorSets", pAllocateInfo->descriptorSetCount, pDescriptorSets, VK_TRUE, VK_TRUE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_vkFreeDescriptorSets(
    debug_report_data*                          report_data,
    VkDescriptorPool                            descriptorPool,
    uint32_t                                    descriptorSetCount,
    const VkDescriptorSet*                      pDescriptorSets)
{
    UNUSED_PARAMETER(descriptorPool);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkFreeDescriptorSets", "descriptorSetCount", "pDescriptorSets", descriptorSetCount, pDescriptorSets, VK_TRUE, VK_TRUE);

    return skipCall;
}

static VkBool32 parameter_validation_vkUpdateDescriptorSets(
    debug_report_data*                          report_data,
    uint32_t                                    descriptorWriteCount,
    const VkWriteDescriptorSet*                 pDescriptorWrites,
    uint32_t                                    descriptorCopyCount,
    const VkCopyDescriptorSet*                  pDescriptorCopies)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type_array(report_data, "vkUpdateDescriptorSets", "descriptorWriteCount", "pDescriptorWrites", "VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET", descriptorWriteCount, pDescriptorWrites, VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET, VK_FALSE, VK_TRUE);

    skipCall |= parameter_validation_VkWriteDescriptorSet(report_data, "vkUpdateDescriptorSets", "pDescriptorWrites->", pDescriptorWrites);

    skipCall |= validate_struct_type_array(report_data, "vkUpdateDescriptorSets", "descriptorCopyCount", "pDescriptorCopies", "VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET", descriptorCopyCount, pDescriptorCopies, VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET, VK_FALSE, VK_TRUE);

    return skipCall;
}

static VkBool32 parameter_validation_vkCreateFramebuffer(
    debug_report_data*                          report_data,
    const VkFramebufferCreateInfo*              pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkFramebuffer*                              pFramebuffer)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkCreateFramebuffer", "pCreateInfo", "VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO", pCreateInfo, VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO, VK_TRUE);

    skipCall |= parameter_validation_VkFramebufferCreateInfo(report_data, "vkCreateFramebuffer", "pCreateInfo->", pCreateInfo);

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkCreateFramebuffer", "pAllocator->", pAllocator);

    skipCall |= validate_required_pointer(report_data, "vkCreateFramebuffer", "pFramebuffer", pFramebuffer);

    return skipCall;
}

static VkBool32 parameter_validation_vkDestroyFramebuffer(
    debug_report_data*                          report_data,
    VkFramebuffer                               framebuffer,
    const VkAllocationCallbacks*                pAllocator)
{
    UNUSED_PARAMETER(framebuffer);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkDestroyFramebuffer", "pAllocator->", pAllocator);

    return skipCall;
}

static VkBool32 parameter_validation_vkCreateRenderPass(
    debug_report_data*                          report_data,
    const VkRenderPassCreateInfo*               pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkRenderPass*                               pRenderPass)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkCreateRenderPass", "pCreateInfo", "VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO", pCreateInfo, VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO, VK_TRUE);

    skipCall |= parameter_validation_VkRenderPassCreateInfo(report_data, "vkCreateRenderPass", "pCreateInfo->", pCreateInfo);

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkCreateRenderPass", "pAllocator->", pAllocator);

    skipCall |= validate_required_pointer(report_data, "vkCreateRenderPass", "pRenderPass", pRenderPass);

    return skipCall;
}

static VkBool32 parameter_validation_vkDestroyRenderPass(
    debug_report_data*                          report_data,
    VkRenderPass                                renderPass,
    const VkAllocationCallbacks*                pAllocator)
{
    UNUSED_PARAMETER(renderPass);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkDestroyRenderPass", "pAllocator->", pAllocator);

    return skipCall;
}

static VkBool32 parameter_validation_vkGetRenderAreaGranularity(
    debug_report_data*                          report_data,
    VkRenderPass                                renderPass,
    VkExtent2D*                                 pGranularity)
{
    UNUSED_PARAMETER(renderPass);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_required_pointer(report_data, "vkGetRenderAreaGranularity", "pGranularity", pGranularity);

    return skipCall;
}

static VkBool32 parameter_validation_vkCreateCommandPool(
    debug_report_data*                          report_data,
    const VkCommandPoolCreateInfo*              pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkCommandPool*                              pCommandPool)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkCreateCommandPool", "pCreateInfo", "VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO", pCreateInfo, VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO, VK_TRUE);

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkCreateCommandPool", "pAllocator->", pAllocator);

    skipCall |= validate_required_pointer(report_data, "vkCreateCommandPool", "pCommandPool", pCommandPool);

    return skipCall;
}

static VkBool32 parameter_validation_vkDestroyCommandPool(
    debug_report_data*                          report_data,
    VkCommandPool                               commandPool,
    const VkAllocationCallbacks*                pAllocator)
{
    UNUSED_PARAMETER(commandPool);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= parameter_validation_VkAllocationCallbacks(report_data, "vkDestroyCommandPool", "pAllocator->", pAllocator);

    return skipCall;
}

static VkBool32 parameter_validation_vkAllocateCommandBuffers(
    debug_report_data*                          report_data,
    const VkCommandBufferAllocateInfo*          pAllocateInfo,
    VkCommandBuffer*                            pCommandBuffers)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkAllocateCommandBuffers", "pAllocateInfo", "VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO", pAllocateInfo, VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO, VK_TRUE);

    if (pAllocateInfo != NULL) {
        skipCall |= validate_array(report_data, "vkAllocateCommandBuffers", "pAllocateInfo->commandBufferCount", "pCommandBuffers", pAllocateInfo->commandBufferCount, pCommandBuffers, VK_TRUE, VK_TRUE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_vkFreeCommandBuffers(
    debug_report_data*                          report_data,
    VkCommandPool                               commandPool,
    uint32_t                                    commandBufferCount,
    const VkCommandBuffer*                      pCommandBuffers)
{
    UNUSED_PARAMETER(commandPool);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkFreeCommandBuffers", "commandBufferCount", "pCommandBuffers", commandBufferCount, pCommandBuffers, VK_TRUE, VK_TRUE);

    return skipCall;
}

static VkBool32 parameter_validation_vkBeginCommandBuffer(
    debug_report_data*                          report_data,
    const VkCommandBufferBeginInfo*             pBeginInfo)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkBeginCommandBuffer", "pBeginInfo", "VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO", pBeginInfo, VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO, VK_TRUE);

    skipCall |= parameter_validation_VkCommandBufferBeginInfo(report_data, "vkBeginCommandBuffer", "pBeginInfo->", pBeginInfo);

    return skipCall;
}

static VkBool32 parameter_validation_vkCmdSetViewport(
    debug_report_data*                          report_data,
    uint32_t                                    firstViewport,
    uint32_t                                    viewportCount,
    const VkViewport*                           pViewports)
{
    UNUSED_PARAMETER(firstViewport);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkCmdSetViewport", "viewportCount", "pViewports", viewportCount, pViewports, VK_TRUE, VK_TRUE);

    return skipCall;
}

static VkBool32 parameter_validation_vkCmdSetScissor(
    debug_report_data*                          report_data,
    uint32_t                                    firstScissor,
    uint32_t                                    scissorCount,
    const VkRect2D*                             pScissors)
{
    UNUSED_PARAMETER(firstScissor);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkCmdSetScissor", "scissorCount", "pScissors", scissorCount, pScissors, VK_TRUE, VK_TRUE);

    return skipCall;
}

static VkBool32 parameter_validation_vkCmdSetBlendConstants(
    debug_report_data*                          report_data,
    const float                                 blendConstants[4])
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_required_pointer(report_data, "vkCmdSetBlendConstants", "blendConstants", blendConstants);

    return skipCall;
}

static VkBool32 parameter_validation_vkCmdBindDescriptorSets(
    debug_report_data*                          report_data,
    VkPipelineBindPoint                         pipelineBindPoint,
    VkPipelineLayout                            layout,
    uint32_t                                    firstSet,
    uint32_t                                    descriptorSetCount,
    const VkDescriptorSet*                      pDescriptorSets,
    uint32_t                                    dynamicOffsetCount,
    const uint32_t*                             pDynamicOffsets)
{
    UNUSED_PARAMETER(pipelineBindPoint);
    UNUSED_PARAMETER(layout);
    UNUSED_PARAMETER(firstSet);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkCmdBindDescriptorSets", "descriptorSetCount", "pDescriptorSets", descriptorSetCount, pDescriptorSets, VK_TRUE, VK_TRUE);

    skipCall |= validate_array(report_data, "vkCmdBindDescriptorSets", "dynamicOffsetCount", "pDynamicOffsets", dynamicOffsetCount, pDynamicOffsets, VK_FALSE, VK_TRUE);

    return skipCall;
}

static VkBool32 parameter_validation_vkCmdBindVertexBuffers(
    debug_report_data*                          report_data,
    uint32_t                                    firstBinding,
    uint32_t                                    bindingCount,
    const VkBuffer*                             pBuffers,
    const VkDeviceSize*                         pOffsets)
{
    UNUSED_PARAMETER(firstBinding);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkCmdBindVertexBuffers", "bindingCount", "pBuffers", bindingCount, pBuffers, VK_TRUE, VK_TRUE);

    skipCall |= validate_array(report_data, "vkCmdBindVertexBuffers", "bindingCount", "pOffsets", bindingCount, pOffsets, VK_TRUE, VK_TRUE);

    return skipCall;
}

static VkBool32 parameter_validation_vkCmdCopyBuffer(
    debug_report_data*                          report_data,
    VkBuffer                                    srcBuffer,
    VkBuffer                                    dstBuffer,
    uint32_t                                    regionCount,
    const VkBufferCopy*                         pRegions)
{
    UNUSED_PARAMETER(srcBuffer);
    UNUSED_PARAMETER(dstBuffer);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkCmdCopyBuffer", "regionCount", "pRegions", regionCount, pRegions, VK_TRUE, VK_TRUE);

    return skipCall;
}

static VkBool32 parameter_validation_vkCmdCopyImage(
    debug_report_data*                          report_data,
    VkImage                                     srcImage,
    VkImageLayout                               srcImageLayout,
    VkImage                                     dstImage,
    VkImageLayout                               dstImageLayout,
    uint32_t                                    regionCount,
    const VkImageCopy*                          pRegions)
{
    UNUSED_PARAMETER(srcImage);
    UNUSED_PARAMETER(srcImageLayout);
    UNUSED_PARAMETER(dstImage);
    UNUSED_PARAMETER(dstImageLayout);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkCmdCopyImage", "regionCount", "pRegions", regionCount, pRegions, VK_TRUE, VK_TRUE);

    return skipCall;
}

static VkBool32 parameter_validation_vkCmdBlitImage(
    debug_report_data*                          report_data,
    VkImage                                     srcImage,
    VkImageLayout                               srcImageLayout,
    VkImage                                     dstImage,
    VkImageLayout                               dstImageLayout,
    uint32_t                                    regionCount,
    const VkImageBlit*                          pRegions,
    VkFilter                                    filter)
{
    UNUSED_PARAMETER(srcImage);
    UNUSED_PARAMETER(srcImageLayout);
    UNUSED_PARAMETER(dstImage);
    UNUSED_PARAMETER(dstImageLayout);
    UNUSED_PARAMETER(filter);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkCmdBlitImage", "regionCount", "pRegions", regionCount, pRegions, VK_TRUE, VK_TRUE);

    return skipCall;
}

static VkBool32 parameter_validation_vkCmdCopyBufferToImage(
    debug_report_data*                          report_data,
    VkBuffer                                    srcBuffer,
    VkImage                                     dstImage,
    VkImageLayout                               dstImageLayout,
    uint32_t                                    regionCount,
    const VkBufferImageCopy*                    pRegions)
{
    UNUSED_PARAMETER(srcBuffer);
    UNUSED_PARAMETER(dstImage);
    UNUSED_PARAMETER(dstImageLayout);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkCmdCopyBufferToImage", "regionCount", "pRegions", regionCount, pRegions, VK_TRUE, VK_TRUE);

    return skipCall;
}

static VkBool32 parameter_validation_vkCmdCopyImageToBuffer(
    debug_report_data*                          report_data,
    VkImage                                     srcImage,
    VkImageLayout                               srcImageLayout,
    VkBuffer                                    dstBuffer,
    uint32_t                                    regionCount,
    const VkBufferImageCopy*                    pRegions)
{
    UNUSED_PARAMETER(srcImage);
    UNUSED_PARAMETER(srcImageLayout);
    UNUSED_PARAMETER(dstBuffer);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkCmdCopyImageToBuffer", "regionCount", "pRegions", regionCount, pRegions, VK_TRUE, VK_TRUE);

    return skipCall;
}

static VkBool32 parameter_validation_vkCmdUpdateBuffer(
    debug_report_data*                          report_data,
    VkBuffer                                    dstBuffer,
    VkDeviceSize                                dstOffset,
    VkDeviceSize                                dataSize,
    const uint32_t*                             pData)
{
    UNUSED_PARAMETER(dstBuffer);
    UNUSED_PARAMETER(dstOffset);
    UNUSED_PARAMETER(dataSize);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkCmdUpdateBuffer", "dataSize", "pData", dataSize, pData, VK_TRUE, VK_TRUE);

    return skipCall;
}

static VkBool32 parameter_validation_vkCmdClearColorImage(
    debug_report_data*                          report_data,
    VkImage                                     image,
    VkImageLayout                               imageLayout,
    const VkClearColorValue*                    pColor,
    uint32_t                                    rangeCount,
    const VkImageSubresourceRange*              pRanges)
{
    UNUSED_PARAMETER(image);
    UNUSED_PARAMETER(imageLayout);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_required_pointer(report_data, "vkCmdClearColorImage", "pColor", pColor);

    skipCall |= validate_array(report_data, "vkCmdClearColorImage", "rangeCount", "pRanges", rangeCount, pRanges, VK_TRUE, VK_TRUE);

    return skipCall;
}

static VkBool32 parameter_validation_vkCmdClearDepthStencilImage(
    debug_report_data*                          report_data,
    VkImage                                     image,
    VkImageLayout                               imageLayout,
    const VkClearDepthStencilValue*             pDepthStencil,
    uint32_t                                    rangeCount,
    const VkImageSubresourceRange*              pRanges)
{
    UNUSED_PARAMETER(image);
    UNUSED_PARAMETER(imageLayout);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_required_pointer(report_data, "vkCmdClearDepthStencilImage", "pDepthStencil", pDepthStencil);

    skipCall |= validate_array(report_data, "vkCmdClearDepthStencilImage", "rangeCount", "pRanges", rangeCount, pRanges, VK_TRUE, VK_TRUE);

    return skipCall;
}

static VkBool32 parameter_validation_vkCmdClearAttachments(
    debug_report_data*                          report_data,
    uint32_t                                    attachmentCount,
    const VkClearAttachment*                    pAttachments,
    uint32_t                                    rectCount,
    const VkClearRect*                          pRects)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkCmdClearAttachments", "attachmentCount", "pAttachments", attachmentCount, pAttachments, VK_TRUE, VK_TRUE);

    skipCall |= validate_array(report_data, "vkCmdClearAttachments", "rectCount", "pRects", rectCount, pRects, VK_TRUE, VK_TRUE);

    return skipCall;
}

static VkBool32 parameter_validation_vkCmdResolveImage(
    debug_report_data*                          report_data,
    VkImage                                     srcImage,
    VkImageLayout                               srcImageLayout,
    VkImage                                     dstImage,
    VkImageLayout                               dstImageLayout,
    uint32_t                                    regionCount,
    const VkImageResolve*                       pRegions)
{
    UNUSED_PARAMETER(srcImage);
    UNUSED_PARAMETER(srcImageLayout);
    UNUSED_PARAMETER(dstImage);
    UNUSED_PARAMETER(dstImageLayout);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkCmdResolveImage", "regionCount", "pRegions", regionCount, pRegions, VK_TRUE, VK_TRUE);

    return skipCall;
}

static VkBool32 parameter_validation_vkCmdWaitEvents(
    debug_report_data*                          report_data,
    uint32_t                                    eventCount,
    const VkEvent*                              pEvents,
    VkPipelineStageFlags                        srcStageMask,
    VkPipelineStageFlags                        dstStageMask,
    uint32_t                                    memoryBarrierCount,
    const VkMemoryBarrier*                      pMemoryBarriers,
    uint32_t                                    bufferMemoryBarrierCount,
    const VkBufferMemoryBarrier*                pBufferMemoryBarriers,
    uint32_t                                    imageMemoryBarrierCount,
    const VkImageMemoryBarrier*                 pImageMemoryBarriers)
{
    UNUSED_PARAMETER(srcStageMask);
    UNUSED_PARAMETER(dstStageMask);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkCmdWaitEvents", "eventCount", "pEvents", eventCount, pEvents, VK_TRUE, VK_TRUE);

    skipCall |= validate_struct_type_array(report_data, "vkCmdWaitEvents", "memoryBarrierCount", "pMemoryBarriers", "VK_STRUCTURE_TYPE_MEMORY_BARRIER", memoryBarrierCount, pMemoryBarriers, VK_STRUCTURE_TYPE_MEMORY_BARRIER, VK_FALSE, VK_TRUE);

    skipCall |= validate_struct_type_array(report_data, "vkCmdWaitEvents", "bufferMemoryBarrierCount", "pBufferMemoryBarriers", "VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER", bufferMemoryBarrierCount, pBufferMemoryBarriers, VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER, VK_FALSE, VK_TRUE);

    skipCall |= validate_struct_type_array(report_data, "vkCmdWaitEvents", "imageMemoryBarrierCount", "pImageMemoryBarriers", "VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER", imageMemoryBarrierCount, pImageMemoryBarriers, VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER, VK_FALSE, VK_TRUE);

    return skipCall;
}

static VkBool32 parameter_validation_vkCmdPipelineBarrier(
    debug_report_data*                          report_data,
    VkPipelineStageFlags                        srcStageMask,
    VkPipelineStageFlags                        dstStageMask,
    VkDependencyFlags                           dependencyFlags,
    uint32_t                                    memoryBarrierCount,
    const VkMemoryBarrier*                      pMemoryBarriers,
    uint32_t                                    bufferMemoryBarrierCount,
    const VkBufferMemoryBarrier*                pBufferMemoryBarriers,
    uint32_t                                    imageMemoryBarrierCount,
    const VkImageMemoryBarrier*                 pImageMemoryBarriers)
{
    UNUSED_PARAMETER(srcStageMask);
    UNUSED_PARAMETER(dstStageMask);
    UNUSED_PARAMETER(dependencyFlags);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type_array(report_data, "vkCmdPipelineBarrier", "memoryBarrierCount", "pMemoryBarriers", "VK_STRUCTURE_TYPE_MEMORY_BARRIER", memoryBarrierCount, pMemoryBarriers, VK_STRUCTURE_TYPE_MEMORY_BARRIER, VK_FALSE, VK_TRUE);

    skipCall |= validate_struct_type_array(report_data, "vkCmdPipelineBarrier", "bufferMemoryBarrierCount", "pBufferMemoryBarriers", "VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER", bufferMemoryBarrierCount, pBufferMemoryBarriers, VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER, VK_FALSE, VK_TRUE);

    skipCall |= validate_struct_type_array(report_data, "vkCmdPipelineBarrier", "imageMemoryBarrierCount", "pImageMemoryBarriers", "VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER", imageMemoryBarrierCount, pImageMemoryBarriers, VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER, VK_FALSE, VK_TRUE);

    return skipCall;
}

static VkBool32 parameter_validation_vkCmdPushConstants(
    debug_report_data*                          report_data,
    VkPipelineLayout                            layout,
    VkShaderStageFlags                          stageFlags,
    uint32_t                                    offset,
    uint32_t                                    size,
    const void*                                 pValues)
{
    UNUSED_PARAMETER(layout);
    UNUSED_PARAMETER(stageFlags);
    UNUSED_PARAMETER(offset);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkCmdPushConstants", "size", "pValues", size, pValues, VK_TRUE, VK_TRUE);

    return skipCall;
}

static VkBool32 parameter_validation_vkCmdBeginRenderPass(
    debug_report_data*                          report_data,
    const VkRenderPassBeginInfo*                pRenderPassBegin,
    VkSubpassContents                           contents)
{
    UNUSED_PARAMETER(contents);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkCmdBeginRenderPass", "pRenderPassBegin", "VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO", pRenderPassBegin, VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO, VK_TRUE);

    skipCall |= parameter_validation_VkRenderPassBeginInfo(report_data, "vkCmdBeginRenderPass", "pRenderPassBegin->", pRenderPassBegin);

    return skipCall;
}

static VkBool32 parameter_validation_vkCmdExecuteCommands(
    debug_report_data*                          report_data,
    uint32_t                                    commandBufferCount,
    const VkCommandBuffer*                      pCommandBuffers)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkCmdExecuteCommands", "commandBufferCount", "pCommandBuffers", commandBufferCount, pCommandBuffers, VK_TRUE, VK_TRUE);

    return skipCall;
}


static VkBool32 parameter_validation_vkGetPhysicalDeviceSurfaceSupportKHR(
    debug_report_data*                          report_data,
    uint32_t                                    queueFamilyIndex,
    VkSurfaceKHR                                surface,
    VkBool32*                                   pSupported)
{
    UNUSED_PARAMETER(queueFamilyIndex);
    UNUSED_PARAMETER(surface);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_required_pointer(report_data, "vkGetPhysicalDeviceSurfaceSupportKHR", "pSupported", pSupported);

    return skipCall;
}

static VkBool32 parameter_validation_vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
    debug_report_data*                          report_data,
    VkSurfaceKHR                                surface,
    VkSurfaceCapabilitiesKHR*                   pSurfaceCapabilities)
{
    UNUSED_PARAMETER(surface);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_required_pointer(report_data, "vkGetPhysicalDeviceSurfaceCapabilitiesKHR", "pSurfaceCapabilities", pSurfaceCapabilities);

    return skipCall;
}

static VkBool32 parameter_validation_vkGetPhysicalDeviceSurfaceFormatsKHR(
    debug_report_data*                          report_data,
    VkSurfaceKHR                                surface,
    uint32_t*                                   pSurfaceFormatCount,
    VkSurfaceFormatKHR*                         pSurfaceFormats)
{
    UNUSED_PARAMETER(surface);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkGetPhysicalDeviceSurfaceFormatsKHR", "pSurfaceFormatCount", "pSurfaceFormats", pSurfaceFormatCount, pSurfaceFormats, VK_TRUE, VK_FALSE, VK_FALSE);

    return skipCall;
}

static VkBool32 parameter_validation_vkGetPhysicalDeviceSurfacePresentModesKHR(
    debug_report_data*                          report_data,
    VkSurfaceKHR                                surface,
    uint32_t*                                   pPresentModeCount,
    VkPresentModeKHR*                           pPresentModes)
{
    UNUSED_PARAMETER(surface);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkGetPhysicalDeviceSurfacePresentModesKHR", "pPresentModeCount", "pPresentModes", pPresentModeCount, pPresentModes, VK_TRUE, VK_FALSE, VK_FALSE);

    return skipCall;
}


static VkBool32 parameter_validation_VkSwapchainCreateInfoKHR(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkSwapchainCreateInfoKHR*              pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_array(report_data, pFuncName, "queueFamilyIndexCount", (std::string(pVariableName) + std::string("pQueueFamilyIndices")).c_str(), pStruct->queueFamilyIndexCount, pStruct->pQueueFamilyIndices, VK_FALSE, VK_TRUE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkPresentInfoKHR(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkPresentInfoKHR*                      pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_array(report_data, pFuncName, "waitSemaphoreCount", (std::string(pVariableName) + std::string("pWaitSemaphores")).c_str(), pStruct->waitSemaphoreCount, pStruct->pWaitSemaphores, VK_TRUE, VK_FALSE);

        skipCall |= validate_array(report_data, pFuncName, "swapchainCount", (std::string(pVariableName) + std::string("pSwapchains")).c_str(), pStruct->swapchainCount, pStruct->pSwapchains, VK_TRUE, VK_TRUE);

        skipCall |= validate_array(report_data, pFuncName, "swapchainCount", (std::string(pVariableName) + std::string("pImageIndices")).c_str(), pStruct->swapchainCount, pStruct->pImageIndices, VK_TRUE, VK_TRUE);

        skipCall |= validate_array(report_data, pFuncName, "swapchainCount", (std::string(pVariableName) + std::string("pResults")).c_str(), pStruct->swapchainCount, pStruct->pResults, VK_TRUE, VK_FALSE);
    }

    return skipCall;
}

static VkBool32 parameter_validation_vkCreateSwapchainKHR(
    debug_report_data*                          report_data,
    const VkSwapchainCreateInfoKHR*             pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSwapchainKHR*                             pSwapchain)
{
    UNUSED_PARAMETER(pAllocator);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkCreateSwapchainKHR", "pCreateInfo", "VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR", pCreateInfo, VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR, VK_TRUE);

    skipCall |= parameter_validation_VkSwapchainCreateInfoKHR(report_data, "vkCreateSwapchainKHR", "pCreateInfo->", pCreateInfo);

    skipCall |= validate_required_pointer(report_data, "vkCreateSwapchainKHR", "pSwapchain", pSwapchain);

    return skipCall;
}

static VkBool32 parameter_validation_vkGetSwapchainImagesKHR(
    debug_report_data*                          report_data,
    VkSwapchainKHR                              swapchain,
    uint32_t*                                   pSwapchainImageCount,
    VkImage*                                    pSwapchainImages)
{
    UNUSED_PARAMETER(swapchain);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkGetSwapchainImagesKHR", "pSwapchainImageCount", "pSwapchainImages", pSwapchainImageCount, pSwapchainImages, VK_TRUE, VK_FALSE, VK_FALSE);

    return skipCall;
}

static VkBool32 parameter_validation_vkAcquireNextImageKHR(
    debug_report_data*                          report_data,
    VkSwapchainKHR                              swapchain,
    uint64_t                                    timeout,
    VkSemaphore                                 semaphore,
    VkFence                                     fence,
    uint32_t*                                   pImageIndex)
{
    UNUSED_PARAMETER(swapchain);
    UNUSED_PARAMETER(timeout);
    UNUSED_PARAMETER(semaphore);
    UNUSED_PARAMETER(fence);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_required_pointer(report_data, "vkAcquireNextImageKHR", "pImageIndex", pImageIndex);

    return skipCall;
}

static VkBool32 parameter_validation_vkQueuePresentKHR(
    debug_report_data*                          report_data,
    const VkPresentInfoKHR*                     pPresentInfo)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkQueuePresentKHR", "pPresentInfo", "VK_STRUCTURE_TYPE_PRESENT_INFO_KHR", pPresentInfo, VK_STRUCTURE_TYPE_PRESENT_INFO_KHR, VK_TRUE);

    skipCall |= parameter_validation_VkPresentInfoKHR(report_data, "vkQueuePresentKHR", "pPresentInfo->", pPresentInfo);

    return skipCall;
}


static VkBool32 parameter_validation_VkDisplayPropertiesKHR(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkDisplayPropertiesKHR*                pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_required_pointer(report_data, pFuncName, (std::string(pVariableName) + std::string("displayName")).c_str(), pStruct->displayName);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkDisplayModeCreateInfoKHR(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkDisplayModeCreateInfoKHR*            pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);
    }

    return skipCall;
}

static VkBool32 parameter_validation_VkDisplaySurfaceCreateInfoKHR(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkDisplaySurfaceCreateInfoKHR*         pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);
    }

    return skipCall;
}

static VkBool32 parameter_validation_vkGetPhysicalDeviceDisplayPropertiesKHR(
    debug_report_data*                          report_data,
    uint32_t*                                   pPropertyCount,
    VkDisplayPropertiesKHR*                     pProperties)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkGetPhysicalDeviceDisplayPropertiesKHR", "pPropertyCount", "pProperties", pPropertyCount, pProperties, VK_TRUE, VK_FALSE, VK_FALSE);

    skipCall |= parameter_validation_VkDisplayPropertiesKHR(report_data, "vkGetPhysicalDeviceDisplayPropertiesKHR", "pProperties->", pProperties);

    return skipCall;
}

static VkBool32 parameter_validation_vkGetPhysicalDeviceDisplayPlanePropertiesKHR(
    debug_report_data*                          report_data,
    uint32_t*                                   pPropertyCount,
    VkDisplayPlanePropertiesKHR*                pProperties)
{
    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkGetPhysicalDeviceDisplayPlanePropertiesKHR", "pPropertyCount", "pProperties", pPropertyCount, pProperties, VK_TRUE, VK_FALSE, VK_FALSE);

    return skipCall;
}

static VkBool32 parameter_validation_vkGetDisplayPlaneSupportedDisplaysKHR(
    debug_report_data*                          report_data,
    uint32_t                                    planeIndex,
    uint32_t*                                   pDisplayCount,
    VkDisplayKHR*                               pDisplays)
{
    UNUSED_PARAMETER(planeIndex);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkGetDisplayPlaneSupportedDisplaysKHR", "pDisplayCount", "pDisplays", pDisplayCount, pDisplays, VK_TRUE, VK_FALSE, VK_FALSE);

    return skipCall;
}

static VkBool32 parameter_validation_vkGetDisplayModePropertiesKHR(
    debug_report_data*                          report_data,
    VkDisplayKHR                                display,
    uint32_t*                                   pPropertyCount,
    VkDisplayModePropertiesKHR*                 pProperties)
{
    UNUSED_PARAMETER(display);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkGetDisplayModePropertiesKHR", "pPropertyCount", "pProperties", pPropertyCount, pProperties, VK_TRUE, VK_FALSE, VK_FALSE);

    return skipCall;
}

static VkBool32 parameter_validation_vkCreateDisplayModeKHR(
    debug_report_data*                          report_data,
    VkDisplayKHR                                display,
    const VkDisplayModeCreateInfoKHR*           pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkDisplayModeKHR*                           pMode)
{
    UNUSED_PARAMETER(display);
    UNUSED_PARAMETER(pAllocator);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkCreateDisplayModeKHR", "pCreateInfo", "VK_STRUCTURE_TYPE_DISPLAY_MODE_CREATE_INFO_KHR", pCreateInfo, VK_STRUCTURE_TYPE_DISPLAY_MODE_CREATE_INFO_KHR, VK_TRUE);

    skipCall |= validate_required_pointer(report_data, "vkCreateDisplayModeKHR", "pMode", pMode);

    return skipCall;
}

static VkBool32 parameter_validation_vkGetDisplayPlaneCapabilitiesKHR(
    debug_report_data*                          report_data,
    VkDisplayModeKHR                            mode,
    uint32_t                                    planeIndex,
    VkDisplayPlaneCapabilitiesKHR*              pCapabilities)
{
    UNUSED_PARAMETER(mode);
    UNUSED_PARAMETER(planeIndex);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_required_pointer(report_data, "vkGetDisplayPlaneCapabilitiesKHR", "pCapabilities", pCapabilities);

    return skipCall;
}

static VkBool32 parameter_validation_vkCreateDisplayPlaneSurfaceKHR(
    debug_report_data*                          report_data,
    const VkDisplaySurfaceCreateInfoKHR*        pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface)
{
    UNUSED_PARAMETER(pAllocator);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkCreateDisplayPlaneSurfaceKHR", "pCreateInfo", "VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR", pCreateInfo, VK_STRUCTURE_TYPE_DISPLAY_SURFACE_CREATE_INFO_KHR, VK_TRUE);

    skipCall |= validate_required_pointer(report_data, "vkCreateDisplayPlaneSurfaceKHR", "pSurface", pSurface);

    return skipCall;
}


static VkBool32 parameter_validation_VkDisplayPresentInfoKHR(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkDisplayPresentInfoKHR*               pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);
    }

    return skipCall;
}

static VkBool32 parameter_validation_vkCreateSharedSwapchainsKHR(
    debug_report_data*                          report_data,
    uint32_t                                    swapchainCount,
    const VkSwapchainCreateInfoKHR*             pCreateInfos,
    const VkAllocationCallbacks*                pAllocator,
    VkSwapchainKHR*                             pSwapchains)
{
    UNUSED_PARAMETER(pAllocator);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_array(report_data, "vkCreateSharedSwapchainsKHR", "swapchainCount", "pCreateInfos", swapchainCount, pCreateInfos, VK_TRUE, VK_TRUE);

    skipCall |= validate_array(report_data, "vkCreateSharedSwapchainsKHR", "swapchainCount", "pSwapchains", swapchainCount, pSwapchains, VK_TRUE, VK_TRUE);

    return skipCall;
}


#ifdef VK_USE_PLATFORM_XLIB_KHR
static VkBool32 parameter_validation_VkXlibSurfaceCreateInfoKHR(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkXlibSurfaceCreateInfoKHR*            pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_required_pointer(report_data, pFuncName, (std::string(pVariableName) + std::string("dpy")).c_str(), pStruct->dpy);
    }

    return skipCall;
}

static VkBool32 parameter_validation_vkCreateXlibSurfaceKHR(
    debug_report_data*                          report_data,
    const VkXlibSurfaceCreateInfoKHR*           pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface)
{
    UNUSED_PARAMETER(pAllocator);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkCreateXlibSurfaceKHR", "pCreateInfo", "VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR", pCreateInfo, VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR, VK_TRUE);

    skipCall |= parameter_validation_VkXlibSurfaceCreateInfoKHR(report_data, "vkCreateXlibSurfaceKHR", "pCreateInfo->", pCreateInfo);

    skipCall |= validate_required_pointer(report_data, "vkCreateXlibSurfaceKHR", "pSurface", pSurface);

    return skipCall;
}

static VkBool32 parameter_validation_vkGetPhysicalDeviceXlibPresentationSupportKHR(
    debug_report_data*                          report_data,
    uint32_t                                    queueFamilyIndex,
    Display*                                    dpy,
    VisualID                                    visualID)
{
    UNUSED_PARAMETER(queueFamilyIndex);
    UNUSED_PARAMETER(visualID);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_required_pointer(report_data, "vkGetPhysicalDeviceXlibPresentationSupportKHR", "dpy", dpy);

    return skipCall;
}
#endif /* VK_USE_PLATFORM_XLIB_KHR */

#ifdef VK_USE_PLATFORM_XCB_KHR
static VkBool32 parameter_validation_VkXcbSurfaceCreateInfoKHR(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkXcbSurfaceCreateInfoKHR*             pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_required_pointer(report_data, pFuncName, (std::string(pVariableName) + std::string("connection")).c_str(), pStruct->connection);
    }

    return skipCall;
}

static VkBool32 parameter_validation_vkCreateXcbSurfaceKHR(
    debug_report_data*                          report_data,
    const VkXcbSurfaceCreateInfoKHR*            pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface)
{
    UNUSED_PARAMETER(pAllocator);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkCreateXcbSurfaceKHR", "pCreateInfo", "VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR", pCreateInfo, VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR, VK_TRUE);

    skipCall |= parameter_validation_VkXcbSurfaceCreateInfoKHR(report_data, "vkCreateXcbSurfaceKHR", "pCreateInfo->", pCreateInfo);

    skipCall |= validate_required_pointer(report_data, "vkCreateXcbSurfaceKHR", "pSurface", pSurface);

    return skipCall;
}

static VkBool32 parameter_validation_vkGetPhysicalDeviceXcbPresentationSupportKHR(
    debug_report_data*                          report_data,
    uint32_t                                    queueFamilyIndex,
    xcb_connection_t*                           connection,
    xcb_visualid_t                              visual_id)
{
    UNUSED_PARAMETER(queueFamilyIndex);
    UNUSED_PARAMETER(visual_id);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_required_pointer(report_data, "vkGetPhysicalDeviceXcbPresentationSupportKHR", "connection", connection);

    return skipCall;
}
#endif /* VK_USE_PLATFORM_XCB_KHR */

#ifdef VK_USE_PLATFORM_WAYLAND_KHR
static VkBool32 parameter_validation_VkWaylandSurfaceCreateInfoKHR(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkWaylandSurfaceCreateInfoKHR*         pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_required_pointer(report_data, pFuncName, (std::string(pVariableName) + std::string("display")).c_str(), pStruct->display);

        skipCall |= validate_required_pointer(report_data, pFuncName, (std::string(pVariableName) + std::string("surface")).c_str(), pStruct->surface);
    }

    return skipCall;
}

static VkBool32 parameter_validation_vkCreateWaylandSurfaceKHR(
    debug_report_data*                          report_data,
    const VkWaylandSurfaceCreateInfoKHR*        pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface)
{
    UNUSED_PARAMETER(pAllocator);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkCreateWaylandSurfaceKHR", "pCreateInfo", "VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR", pCreateInfo, VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR, VK_TRUE);

    skipCall |= parameter_validation_VkWaylandSurfaceCreateInfoKHR(report_data, "vkCreateWaylandSurfaceKHR", "pCreateInfo->", pCreateInfo);

    skipCall |= validate_required_pointer(report_data, "vkCreateWaylandSurfaceKHR", "pSurface", pSurface);

    return skipCall;
}

static VkBool32 parameter_validation_vkGetPhysicalDeviceWaylandPresentationSupportKHR(
    debug_report_data*                          report_data,
    uint32_t                                    queueFamilyIndex,
    struct wl_display*                          display)
{
    UNUSED_PARAMETER(queueFamilyIndex);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_required_pointer(report_data, "vkGetPhysicalDeviceWaylandPresentationSupportKHR", "display", display);

    return skipCall;
}
#endif /* VK_USE_PLATFORM_WAYLAND_KHR */

#ifdef VK_USE_PLATFORM_MIR_KHR
static VkBool32 parameter_validation_VkMirSurfaceCreateInfoKHR(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkMirSurfaceCreateInfoKHR*             pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_required_pointer(report_data, pFuncName, (std::string(pVariableName) + std::string("connection")).c_str(), pStruct->connection);

        skipCall |= validate_required_pointer(report_data, pFuncName, (std::string(pVariableName) + std::string("mirSurface")).c_str(), pStruct->mirSurface);
    }

    return skipCall;
}

static VkBool32 parameter_validation_vkCreateMirSurfaceKHR(
    debug_report_data*                          report_data,
    const VkMirSurfaceCreateInfoKHR*            pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface)
{
    UNUSED_PARAMETER(pAllocator);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkCreateMirSurfaceKHR", "pCreateInfo", "VK_STRUCTURE_TYPE_MIR_SURFACE_CREATE_INFO_KHR", pCreateInfo, VK_STRUCTURE_TYPE_MIR_SURFACE_CREATE_INFO_KHR, VK_TRUE);

    skipCall |= parameter_validation_VkMirSurfaceCreateInfoKHR(report_data, "vkCreateMirSurfaceKHR", "pCreateInfo->", pCreateInfo);

    skipCall |= validate_required_pointer(report_data, "vkCreateMirSurfaceKHR", "pSurface", pSurface);

    return skipCall;
}

static VkBool32 parameter_validation_vkGetPhysicalDeviceMirPresentationSupportKHR(
    debug_report_data*                          report_data,
    uint32_t                                    queueFamilyIndex,
    MirConnection*                              connection)
{
    UNUSED_PARAMETER(queueFamilyIndex);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_required_pointer(report_data, "vkGetPhysicalDeviceMirPresentationSupportKHR", "connection", connection);

    return skipCall;
}
#endif /* VK_USE_PLATFORM_MIR_KHR */

#ifdef VK_USE_PLATFORM_ANDROID_KHR
static VkBool32 parameter_validation_VkAndroidSurfaceCreateInfoKHR(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkAndroidSurfaceCreateInfoKHR*         pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_required_pointer(report_data, pFuncName, (std::string(pVariableName) + std::string("window")).c_str(), pStruct->window);
    }

    return skipCall;
}

static VkBool32 parameter_validation_vkCreateAndroidSurfaceKHR(
    debug_report_data*                          report_data,
    const VkAndroidSurfaceCreateInfoKHR*        pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface)
{
    UNUSED_PARAMETER(pAllocator);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkCreateAndroidSurfaceKHR", "pCreateInfo", "VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR", pCreateInfo, VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR, VK_TRUE);

    skipCall |= parameter_validation_VkAndroidSurfaceCreateInfoKHR(report_data, "vkCreateAndroidSurfaceKHR", "pCreateInfo->", pCreateInfo);

    skipCall |= validate_required_pointer(report_data, "vkCreateAndroidSurfaceKHR", "pSurface", pSurface);

    return skipCall;
}
#endif /* VK_USE_PLATFORM_ANDROID_KHR */

#ifdef VK_USE_PLATFORM_WIN32_KHR
static VkBool32 parameter_validation_VkWin32SurfaceCreateInfoKHR(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkWin32SurfaceCreateInfoKHR*           pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);
    }

    return skipCall;
}

static VkBool32 parameter_validation_vkCreateWin32SurfaceKHR(
    debug_report_data*                          report_data,
    const VkWin32SurfaceCreateInfoKHR*          pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface)
{
    UNUSED_PARAMETER(pAllocator);

    VkBool32 skipCall = VK_FALSE;

    skipCall |= validate_struct_type(report_data, "vkCreateWin32SurfaceKHR", "pCreateInfo", "VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR", pCreateInfo, VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR, VK_TRUE);

    skipCall |= validate_required_pointer(report_data, "vkCreateWin32SurfaceKHR", "pSurface", pSurface);

    return skipCall;
}
#endif /* VK_USE_PLATFORM_WIN32_KHR */

static VkBool32 parameter_validation_VkDebugReportCallbackCreateInfoEXT(
    debug_report_data*                           report_data,
    const char*                                  pFuncName,
    const char*                                  pVariableName,
    const VkDebugReportCallbackCreateInfoEXT*    pStruct)
{
    VkBool32 skipCall = VK_FALSE;

    if (pStruct != NULL) {
        skipCall |= validate_struct_pnext(report_data, pFuncName, (std::string(pVariableName) + std::string("pNext")).c_str(), NULL, pStruct->pNext, 0, NULL);

        skipCall |= validate_required_pointer(report_data, pFuncName, (std::string(pVariableName) + std::string("pfnCallback")).c_str(), reinterpret_cast<const void*>(pStruct->pfnCallback));
    }

    return skipCall;
}



#endif
