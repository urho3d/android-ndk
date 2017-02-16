/* THIS FILE IS GENERATED.  DO NOT EDIT. */

/*
 * Copyright (c) 2015-2016 The Khronos Group Inc.
 * Copyright (c) 2015-2016 Valve Corporation
 * Copyright (c) 2015-2016 LunarG, Inc.
 * Copyright (c) 2015-2016 Google, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Author: Tobin Ehlis <tobine@google.com>
 * Author: Courtney Goeltzenleuchter <courtneygo@google.com>
 * Author: Jon Ashburn <jon@lunarg.com>
 * Author: Mark Lobodzinski <mark@lunarg.com>
 * Author: Mike Stroyan <stroyan@google.com>
 * Author: Tony Barbour <tony@LunarG.com>
 */

// CODEGEN : file ../vk-layer-generate.py line #749
#include "unique_objects.h"

namespace unique_objects {

VKAPI_ATTR VkResult VKAPI_CALL CreateInstance(const VkInstanceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkInstance* pInstance)
{
    return explicit_CreateInstance(pCreateInfo, pAllocator, pInstance);
}

VKAPI_ATTR void VKAPI_CALL DestroyInstance(VkInstance instance, const VkAllocationCallbacks* pAllocator)
{
    return explicit_DestroyInstance(instance, pAllocator);
}

VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL GetInstanceProcAddr(VkInstance instance, const char* pName);

VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL GetDeviceProcAddr(VkDevice device, const char* pName);

VKAPI_ATTR VkResult VKAPI_CALL CreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDevice* pDevice)
{
    return explicit_CreateDevice(physicalDevice, pCreateInfo, pAllocator, pDevice);
}

VKAPI_ATTR void VKAPI_CALL DestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator)
{
    return explicit_DestroyDevice(device, pAllocator);
}

VKAPI_ATTR VkResult VKAPI_CALL EnumerateInstanceExtensionProperties(const char* pLayerName, uint32_t* pPropertyCount, VkExtensionProperties* pProperties);

VKAPI_ATTR VkResult VKAPI_CALL EnumerateInstanceLayerProperties(uint32_t* pPropertyCount, VkLayerProperties* pProperties);

VKAPI_ATTR VkResult VKAPI_CALL EnumerateDeviceLayerProperties(VkPhysicalDevice physicalDevice, uint32_t* pPropertyCount, VkLayerProperties* pProperties);

VKAPI_ATTR VkResult VKAPI_CALL QueueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo* pSubmits, VkFence fence)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(queue), layer_data_map);
// STRUCT USES:['fence', 'pSubmits[submitCount]']
//LOCAL DECLS:['pSubmits']
    safe_VkSubmitInfo* local_pSubmits = NULL;
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    fence = (VkFence)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(fence)];
    if (pSubmits) {
        local_pSubmits = new safe_VkSubmitInfo[submitCount];
        for (uint32_t idx0=0; idx0<submitCount; ++idx0) {
            local_pSubmits[idx0].initialize(&pSubmits[idx0]);
            if (local_pSubmits[idx0].pSignalSemaphores) {
                for (uint32_t idx1=0; idx1<pSubmits[idx0].signalSemaphoreCount; ++idx1) {
                    local_pSubmits[idx0].pSignalSemaphores[idx1] = (VkSemaphore)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pSubmits[idx0].pSignalSemaphores[idx1])];
                }
            }
            if (local_pSubmits[idx0].pWaitSemaphores) {
                for (uint32_t idx2=0; idx2<pSubmits[idx0].waitSemaphoreCount; ++idx2) {
                    local_pSubmits[idx0].pWaitSemaphores[idx2] = (VkSemaphore)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pSubmits[idx0].pWaitSemaphores[idx2])];
                }
            }
        }
    }
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, queue)->QueueSubmit(queue, submitCount, (const VkSubmitInfo*)local_pSubmits, fence);
    if (local_pSubmits)
        delete[] local_pSubmits;
    return result;
}


VKAPI_ATTR VkResult VKAPI_CALL AllocateMemory(VkDevice device, const VkMemoryAllocateInfo* pAllocateInfo, const VkAllocationCallbacks* pAllocator, VkDeviceMemory* pMemory)
{
    return explicit_AllocateMemory(device, pAllocateInfo, pAllocator, pMemory);
}

VKAPI_ATTR void VKAPI_CALL FreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks* pAllocator)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['memory']
    std::unique_lock<std::mutex> lock(global_lock);
    uint64_t local_memory = reinterpret_cast<uint64_t &>(memory);
    memory = (VkDeviceMemory)my_map_data->unique_id_mapping[local_memory];
    my_map_data->unique_id_mapping.erase(local_memory);
    lock.unlock();
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, device)->FreeMemory(device, memory, pAllocator);
}


VKAPI_ATTR VkResult VKAPI_CALL MapMemory(VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void** ppData)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['memory']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    memory = (VkDeviceMemory)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(memory)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->MapMemory(device, memory, offset, size, flags, ppData);
    return result;
}


VKAPI_ATTR void VKAPI_CALL UnmapMemory(VkDevice device, VkDeviceMemory memory)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['memory']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    memory = (VkDeviceMemory)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(memory)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, device)->UnmapMemory(device, memory);
}


VKAPI_ATTR VkResult VKAPI_CALL FlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['pMemoryRanges[memoryRangeCount]']
//LOCAL DECLS:['pMemoryRanges']
    safe_VkMappedMemoryRange* local_pMemoryRanges = NULL;
    {
    std::lock_guard<std::mutex> lock(global_lock);
    if (pMemoryRanges) {
        local_pMemoryRanges = new safe_VkMappedMemoryRange[memoryRangeCount];
        for (uint32_t idx0=0; idx0<memoryRangeCount; ++idx0) {
            local_pMemoryRanges[idx0].initialize(&pMemoryRanges[idx0]);
            if (pMemoryRanges[idx0].memory) {
                local_pMemoryRanges[idx0].memory = (VkDeviceMemory)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pMemoryRanges[idx0].memory)];
            }
        }
    }
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->FlushMappedMemoryRanges(device, memoryRangeCount, (const VkMappedMemoryRange*)local_pMemoryRanges);
    if (local_pMemoryRanges)
        delete[] local_pMemoryRanges;
    return result;
}


VKAPI_ATTR VkResult VKAPI_CALL InvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange* pMemoryRanges)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['pMemoryRanges[memoryRangeCount]']
//LOCAL DECLS:['pMemoryRanges']
    safe_VkMappedMemoryRange* local_pMemoryRanges = NULL;
    {
    std::lock_guard<std::mutex> lock(global_lock);
    if (pMemoryRanges) {
        local_pMemoryRanges = new safe_VkMappedMemoryRange[memoryRangeCount];
        for (uint32_t idx0=0; idx0<memoryRangeCount; ++idx0) {
            local_pMemoryRanges[idx0].initialize(&pMemoryRanges[idx0]);
            if (pMemoryRanges[idx0].memory) {
                local_pMemoryRanges[idx0].memory = (VkDeviceMemory)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pMemoryRanges[idx0].memory)];
            }
        }
    }
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->InvalidateMappedMemoryRanges(device, memoryRangeCount, (const VkMappedMemoryRange*)local_pMemoryRanges);
    if (local_pMemoryRanges)
        delete[] local_pMemoryRanges;
    return result;
}


VKAPI_ATTR void VKAPI_CALL GetDeviceMemoryCommitment(VkDevice device, VkDeviceMemory memory, VkDeviceSize* pCommittedMemoryInBytes)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['memory']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    memory = (VkDeviceMemory)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(memory)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, device)->GetDeviceMemoryCommitment(device, memory, pCommittedMemoryInBytes);
}


VKAPI_ATTR VkResult VKAPI_CALL BindBufferMemory(VkDevice device, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['buffer', 'memory']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    buffer = (VkBuffer)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(buffer)];
// CODEGEN : file ../vk-layer-generate.py line #842
    memory = (VkDeviceMemory)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(memory)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->BindBufferMemory(device, buffer, memory, memoryOffset);
    return result;
}


VKAPI_ATTR VkResult VKAPI_CALL BindImageMemory(VkDevice device, VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['image', 'memory']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    image = (VkImage)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(image)];
// CODEGEN : file ../vk-layer-generate.py line #842
    memory = (VkDeviceMemory)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(memory)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->BindImageMemory(device, image, memory, memoryOffset);
    return result;
}


VKAPI_ATTR void VKAPI_CALL GetBufferMemoryRequirements(VkDevice device, VkBuffer buffer, VkMemoryRequirements* pMemoryRequirements)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['buffer']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    buffer = (VkBuffer)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(buffer)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, device)->GetBufferMemoryRequirements(device, buffer, pMemoryRequirements);
}


VKAPI_ATTR void VKAPI_CALL GetImageMemoryRequirements(VkDevice device, VkImage image, VkMemoryRequirements* pMemoryRequirements)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['image']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    image = (VkImage)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(image)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, device)->GetImageMemoryRequirements(device, image, pMemoryRequirements);
}


VKAPI_ATTR void VKAPI_CALL GetImageSparseMemoryRequirements(VkDevice device, VkImage image, uint32_t* pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements* pSparseMemoryRequirements)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['image']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    image = (VkImage)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(image)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, device)->GetImageSparseMemoryRequirements(device, image, pSparseMemoryRequirementCount, pSparseMemoryRequirements);
}


VKAPI_ATTR VkResult VKAPI_CALL QueueBindSparse(VkQueue queue, uint32_t bindInfoCount, const VkBindSparseInfo* pBindInfo, VkFence fence)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(queue), layer_data_map);
// STRUCT USES:['fence', 'pBindInfo[bindInfoCount]']
//LOCAL DECLS:['pBindInfo']
    safe_VkBindSparseInfo* local_pBindInfo = NULL;
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    fence = (VkFence)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(fence)];
    if (pBindInfo) {
        local_pBindInfo = new safe_VkBindSparseInfo[bindInfoCount];
        for (uint32_t idx0=0; idx0<bindInfoCount; ++idx0) {
            local_pBindInfo[idx0].initialize(&pBindInfo[idx0]);
            if (local_pBindInfo[idx0].pBufferBinds) {
                for (uint32_t idx1=0; idx1<pBindInfo[idx0].bufferBindCount; ++idx1) {
                    if (pBindInfo[idx0].pBufferBinds[idx1].buffer) {
                        local_pBindInfo[idx0].pBufferBinds[idx1].buffer = (VkBuffer)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pBindInfo[idx0].pBufferBinds[idx1].buffer)];
                    }
                    if (local_pBindInfo[idx0].pBufferBinds[idx1].pBinds) {
                        for (uint32_t idx2=0; idx2<pBindInfo[idx0].pBufferBinds[idx1].bindCount; ++idx2) {
                            if (pBindInfo[idx0].pBufferBinds[idx1].pBinds[idx2].memory) {
                                local_pBindInfo[idx0].pBufferBinds[idx1].pBinds[idx2].memory = (VkDeviceMemory)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pBindInfo[idx0].pBufferBinds[idx1].pBinds[idx2].memory)];
                            }
                        }
                    }
                }
            }
            if (local_pBindInfo[idx0].pImageBinds) {
                for (uint32_t idx2=0; idx2<pBindInfo[idx0].imageBindCount; ++idx2) {
                    if (pBindInfo[idx0].pImageBinds[idx2].image) {
                        local_pBindInfo[idx0].pImageBinds[idx2].image = (VkImage)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pBindInfo[idx0].pImageBinds[idx2].image)];
                    }
                    if (local_pBindInfo[idx0].pImageBinds[idx2].pBinds) {
                        for (uint32_t idx3=0; idx3<pBindInfo[idx0].pImageBinds[idx2].bindCount; ++idx3) {
                            if (pBindInfo[idx0].pImageBinds[idx2].pBinds[idx3].memory) {
                                local_pBindInfo[idx0].pImageBinds[idx2].pBinds[idx3].memory = (VkDeviceMemory)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pBindInfo[idx0].pImageBinds[idx2].pBinds[idx3].memory)];
                            }
                        }
                    }
                }
            }
            if (local_pBindInfo[idx0].pImageOpaqueBinds) {
                for (uint32_t idx3=0; idx3<pBindInfo[idx0].imageOpaqueBindCount; ++idx3) {
                    if (pBindInfo[idx0].pImageOpaqueBinds[idx3].image) {
                        local_pBindInfo[idx0].pImageOpaqueBinds[idx3].image = (VkImage)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pBindInfo[idx0].pImageOpaqueBinds[idx3].image)];
                    }
                    if (local_pBindInfo[idx0].pImageOpaqueBinds[idx3].pBinds) {
                        for (uint32_t idx4=0; idx4<pBindInfo[idx0].pImageOpaqueBinds[idx3].bindCount; ++idx4) {
                            if (pBindInfo[idx0].pImageOpaqueBinds[idx3].pBinds[idx4].memory) {
                                local_pBindInfo[idx0].pImageOpaqueBinds[idx3].pBinds[idx4].memory = (VkDeviceMemory)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pBindInfo[idx0].pImageOpaqueBinds[idx3].pBinds[idx4].memory)];
                            }
                        }
                    }
                }
            }
            if (local_pBindInfo[idx0].pSignalSemaphores) {
                for (uint32_t idx4=0; idx4<pBindInfo[idx0].signalSemaphoreCount; ++idx4) {
                    local_pBindInfo[idx0].pSignalSemaphores[idx4] = (VkSemaphore)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pBindInfo[idx0].pSignalSemaphores[idx4])];
                }
            }
            if (local_pBindInfo[idx0].pWaitSemaphores) {
                for (uint32_t idx5=0; idx5<pBindInfo[idx0].waitSemaphoreCount; ++idx5) {
                    local_pBindInfo[idx0].pWaitSemaphores[idx5] = (VkSemaphore)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pBindInfo[idx0].pWaitSemaphores[idx5])];
                }
            }
        }
    }
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, queue)->QueueBindSparse(queue, bindInfoCount, (const VkBindSparseInfo*)local_pBindInfo, fence);
    if (local_pBindInfo)
        delete[] local_pBindInfo;
    return result;
}


VKAPI_ATTR VkResult VKAPI_CALL CreateFence(VkDevice device, const VkFenceCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFence* pFence)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateFence(device, pCreateInfo, pAllocator, pFence);
    if (VK_SUCCESS == result) {
        std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #961
        uint64_t unique_id = global_unique_id++;
        my_map_data->unique_id_mapping[unique_id] = reinterpret_cast<uint64_t &>(*pFence);
        *pFence = reinterpret_cast<VkFence&>(unique_id);
    }
    return result;
}


VKAPI_ATTR void VKAPI_CALL DestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks* pAllocator)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['fence']
    std::unique_lock<std::mutex> lock(global_lock);
    uint64_t local_fence = reinterpret_cast<uint64_t &>(fence);
    fence = (VkFence)my_map_data->unique_id_mapping[local_fence];
    my_map_data->unique_id_mapping.erase(local_fence);
    lock.unlock();
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyFence(device, fence, pAllocator);
}


VKAPI_ATTR VkResult VKAPI_CALL ResetFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['pFences[fenceCount]']
//LOCAL DECLS:['pFences']
    VkFence* local_pFences = NULL;
    {
    std::lock_guard<std::mutex> lock(global_lock);
    if (pFences) {
        local_pFences = new VkFence[fenceCount];
        for (uint32_t idx0=0; idx0<fenceCount; ++idx0) {
            local_pFences[idx0] = (VkFence)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pFences[idx0])];
        }
    }
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->ResetFences(device, fenceCount, (const VkFence*)local_pFences);
    if (local_pFences)
        delete[] local_pFences;
    return result;
}


VKAPI_ATTR VkResult VKAPI_CALL GetFenceStatus(VkDevice device, VkFence fence)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['fence']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    fence = (VkFence)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(fence)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->GetFenceStatus(device, fence);
    return result;
}


VKAPI_ATTR VkResult VKAPI_CALL WaitForFences(VkDevice device, uint32_t fenceCount, const VkFence* pFences, VkBool32 waitAll, uint64_t timeout)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['pFences[fenceCount]']
//LOCAL DECLS:['pFences']
    VkFence* local_pFences = NULL;
    {
    std::lock_guard<std::mutex> lock(global_lock);
    if (pFences) {
        local_pFences = new VkFence[fenceCount];
        for (uint32_t idx0=0; idx0<fenceCount; ++idx0) {
            local_pFences[idx0] = (VkFence)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pFences[idx0])];
        }
    }
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->WaitForFences(device, fenceCount, (const VkFence*)local_pFences, waitAll, timeout);
    if (local_pFences)
        delete[] local_pFences;
    return result;
}


VKAPI_ATTR VkResult VKAPI_CALL CreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSemaphore* pSemaphore)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateSemaphore(device, pCreateInfo, pAllocator, pSemaphore);
    if (VK_SUCCESS == result) {
        std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #961
        uint64_t unique_id = global_unique_id++;
        my_map_data->unique_id_mapping[unique_id] = reinterpret_cast<uint64_t &>(*pSemaphore);
        *pSemaphore = reinterpret_cast<VkSemaphore&>(unique_id);
    }
    return result;
}


VKAPI_ATTR void VKAPI_CALL DestroySemaphore(VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks* pAllocator)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['semaphore']
    std::unique_lock<std::mutex> lock(global_lock);
    uint64_t local_semaphore = reinterpret_cast<uint64_t &>(semaphore);
    semaphore = (VkSemaphore)my_map_data->unique_id_mapping[local_semaphore];
    my_map_data->unique_id_mapping.erase(local_semaphore);
    lock.unlock();
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, device)->DestroySemaphore(device, semaphore, pAllocator);
}


VKAPI_ATTR VkResult VKAPI_CALL CreateEvent(VkDevice device, const VkEventCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkEvent* pEvent)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateEvent(device, pCreateInfo, pAllocator, pEvent);
    if (VK_SUCCESS == result) {
        std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #961
        uint64_t unique_id = global_unique_id++;
        my_map_data->unique_id_mapping[unique_id] = reinterpret_cast<uint64_t &>(*pEvent);
        *pEvent = reinterpret_cast<VkEvent&>(unique_id);
    }
    return result;
}


VKAPI_ATTR void VKAPI_CALL DestroyEvent(VkDevice device, VkEvent event, const VkAllocationCallbacks* pAllocator)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['event']
    std::unique_lock<std::mutex> lock(global_lock);
    uint64_t local_event = reinterpret_cast<uint64_t &>(event);
    event = (VkEvent)my_map_data->unique_id_mapping[local_event];
    my_map_data->unique_id_mapping.erase(local_event);
    lock.unlock();
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyEvent(device, event, pAllocator);
}


VKAPI_ATTR VkResult VKAPI_CALL GetEventStatus(VkDevice device, VkEvent event)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['event']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    event = (VkEvent)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(event)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->GetEventStatus(device, event);
    return result;
}


VKAPI_ATTR VkResult VKAPI_CALL SetEvent(VkDevice device, VkEvent event)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['event']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    event = (VkEvent)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(event)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->SetEvent(device, event);
    return result;
}


VKAPI_ATTR VkResult VKAPI_CALL ResetEvent(VkDevice device, VkEvent event)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['event']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    event = (VkEvent)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(event)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->ResetEvent(device, event);
    return result;
}


VKAPI_ATTR VkResult VKAPI_CALL CreateQueryPool(VkDevice device, const VkQueryPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkQueryPool* pQueryPool)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateQueryPool(device, pCreateInfo, pAllocator, pQueryPool);
    if (VK_SUCCESS == result) {
        std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #961
        uint64_t unique_id = global_unique_id++;
        my_map_data->unique_id_mapping[unique_id] = reinterpret_cast<uint64_t &>(*pQueryPool);
        *pQueryPool = reinterpret_cast<VkQueryPool&>(unique_id);
    }
    return result;
}


VKAPI_ATTR void VKAPI_CALL DestroyQueryPool(VkDevice device, VkQueryPool queryPool, const VkAllocationCallbacks* pAllocator)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['queryPool']
    std::unique_lock<std::mutex> lock(global_lock);
    uint64_t local_queryPool = reinterpret_cast<uint64_t &>(queryPool);
    queryPool = (VkQueryPool)my_map_data->unique_id_mapping[local_queryPool];
    my_map_data->unique_id_mapping.erase(local_queryPool);
    lock.unlock();
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyQueryPool(device, queryPool, pAllocator);
}


VKAPI_ATTR VkResult VKAPI_CALL GetQueryPoolResults(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void* pData, VkDeviceSize stride, VkQueryResultFlags flags)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['queryPool']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    queryPool = (VkQueryPool)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(queryPool)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->GetQueryPoolResults(device, queryPool, firstQuery, queryCount, dataSize, pData, stride, flags);
    return result;
}


VKAPI_ATTR VkResult VKAPI_CALL CreateBuffer(VkDevice device, const VkBufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBuffer* pBuffer)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateBuffer(device, pCreateInfo, pAllocator, pBuffer);
    if (VK_SUCCESS == result) {
        std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #961
        uint64_t unique_id = global_unique_id++;
        my_map_data->unique_id_mapping[unique_id] = reinterpret_cast<uint64_t &>(*pBuffer);
        *pBuffer = reinterpret_cast<VkBuffer&>(unique_id);
    }
    return result;
}


VKAPI_ATTR void VKAPI_CALL DestroyBuffer(VkDevice device, VkBuffer buffer, const VkAllocationCallbacks* pAllocator)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['buffer']
    std::unique_lock<std::mutex> lock(global_lock);
    uint64_t local_buffer = reinterpret_cast<uint64_t &>(buffer);
    buffer = (VkBuffer)my_map_data->unique_id_mapping[local_buffer];
    my_map_data->unique_id_mapping.erase(local_buffer);
    lock.unlock();
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyBuffer(device, buffer, pAllocator);
}


VKAPI_ATTR VkResult VKAPI_CALL CreateBufferView(VkDevice device, const VkBufferViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkBufferView* pView)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['pCreateInfo']
//LOCAL DECLS:['pCreateInfo']
    safe_VkBufferViewCreateInfo* local_pCreateInfo = NULL;
    {
    std::lock_guard<std::mutex> lock(global_lock);
    if (pCreateInfo) {
        local_pCreateInfo = new safe_VkBufferViewCreateInfo(pCreateInfo);
// CODEGEN : file ../vk-layer-generate.py line #842
        local_pCreateInfo->buffer = (VkBuffer)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pCreateInfo->buffer)];
    }
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateBufferView(device, (const VkBufferViewCreateInfo*)local_pCreateInfo, pAllocator, pView);
    if (local_pCreateInfo)
        delete local_pCreateInfo;
    if (VK_SUCCESS == result) {
        std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #961
        uint64_t unique_id = global_unique_id++;
        my_map_data->unique_id_mapping[unique_id] = reinterpret_cast<uint64_t &>(*pView);
        *pView = reinterpret_cast<VkBufferView&>(unique_id);
    }
    return result;
}


VKAPI_ATTR void VKAPI_CALL DestroyBufferView(VkDevice device, VkBufferView bufferView, const VkAllocationCallbacks* pAllocator)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['bufferView']
    std::unique_lock<std::mutex> lock(global_lock);
    uint64_t local_bufferView = reinterpret_cast<uint64_t &>(bufferView);
    bufferView = (VkBufferView)my_map_data->unique_id_mapping[local_bufferView];
    my_map_data->unique_id_mapping.erase(local_bufferView);
    lock.unlock();
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyBufferView(device, bufferView, pAllocator);
}


VKAPI_ATTR VkResult VKAPI_CALL CreateImage(VkDevice device, const VkImageCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImage* pImage)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateImage(device, pCreateInfo, pAllocator, pImage);
    if (VK_SUCCESS == result) {
        std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #961
        uint64_t unique_id = global_unique_id++;
        my_map_data->unique_id_mapping[unique_id] = reinterpret_cast<uint64_t &>(*pImage);
        *pImage = reinterpret_cast<VkImage&>(unique_id);
    }
    return result;
}


VKAPI_ATTR void VKAPI_CALL DestroyImage(VkDevice device, VkImage image, const VkAllocationCallbacks* pAllocator)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['image']
    std::unique_lock<std::mutex> lock(global_lock);
    uint64_t local_image = reinterpret_cast<uint64_t &>(image);
    image = (VkImage)my_map_data->unique_id_mapping[local_image];
    my_map_data->unique_id_mapping.erase(local_image);
    lock.unlock();
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyImage(device, image, pAllocator);
}


VKAPI_ATTR void VKAPI_CALL GetImageSubresourceLayout(VkDevice device, VkImage image, const VkImageSubresource* pSubresource, VkSubresourceLayout* pLayout)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['image']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    image = (VkImage)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(image)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, device)->GetImageSubresourceLayout(device, image, pSubresource, pLayout);
}


VKAPI_ATTR VkResult VKAPI_CALL CreateImageView(VkDevice device, const VkImageViewCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkImageView* pView)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['pCreateInfo']
//LOCAL DECLS:['pCreateInfo']
    safe_VkImageViewCreateInfo* local_pCreateInfo = NULL;
    {
    std::lock_guard<std::mutex> lock(global_lock);
    if (pCreateInfo) {
        local_pCreateInfo = new safe_VkImageViewCreateInfo(pCreateInfo);
// CODEGEN : file ../vk-layer-generate.py line #842
        local_pCreateInfo->image = (VkImage)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pCreateInfo->image)];
    }
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateImageView(device, (const VkImageViewCreateInfo*)local_pCreateInfo, pAllocator, pView);
    if (local_pCreateInfo)
        delete local_pCreateInfo;
    if (VK_SUCCESS == result) {
        std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #961
        uint64_t unique_id = global_unique_id++;
        my_map_data->unique_id_mapping[unique_id] = reinterpret_cast<uint64_t &>(*pView);
        *pView = reinterpret_cast<VkImageView&>(unique_id);
    }
    return result;
}


VKAPI_ATTR void VKAPI_CALL DestroyImageView(VkDevice device, VkImageView imageView, const VkAllocationCallbacks* pAllocator)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['imageView']
    std::unique_lock<std::mutex> lock(global_lock);
    uint64_t local_imageView = reinterpret_cast<uint64_t &>(imageView);
    imageView = (VkImageView)my_map_data->unique_id_mapping[local_imageView];
    my_map_data->unique_id_mapping.erase(local_imageView);
    lock.unlock();
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyImageView(device, imageView, pAllocator);
}


VKAPI_ATTR VkResult VKAPI_CALL CreateShaderModule(VkDevice device, const VkShaderModuleCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkShaderModule* pShaderModule)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateShaderModule(device, pCreateInfo, pAllocator, pShaderModule);
    if (VK_SUCCESS == result) {
        std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #961
        uint64_t unique_id = global_unique_id++;
        my_map_data->unique_id_mapping[unique_id] = reinterpret_cast<uint64_t &>(*pShaderModule);
        *pShaderModule = reinterpret_cast<VkShaderModule&>(unique_id);
    }
    return result;
}


VKAPI_ATTR void VKAPI_CALL DestroyShaderModule(VkDevice device, VkShaderModule shaderModule, const VkAllocationCallbacks* pAllocator)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['shaderModule']
    std::unique_lock<std::mutex> lock(global_lock);
    uint64_t local_shaderModule = reinterpret_cast<uint64_t &>(shaderModule);
    shaderModule = (VkShaderModule)my_map_data->unique_id_mapping[local_shaderModule];
    my_map_data->unique_id_mapping.erase(local_shaderModule);
    lock.unlock();
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyShaderModule(device, shaderModule, pAllocator);
}


VKAPI_ATTR VkResult VKAPI_CALL CreatePipelineCache(VkDevice device, const VkPipelineCacheCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineCache* pPipelineCache)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreatePipelineCache(device, pCreateInfo, pAllocator, pPipelineCache);
    if (VK_SUCCESS == result) {
        std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #961
        uint64_t unique_id = global_unique_id++;
        my_map_data->unique_id_mapping[unique_id] = reinterpret_cast<uint64_t &>(*pPipelineCache);
        *pPipelineCache = reinterpret_cast<VkPipelineCache&>(unique_id);
    }
    return result;
}


VKAPI_ATTR void VKAPI_CALL DestroyPipelineCache(VkDevice device, VkPipelineCache pipelineCache, const VkAllocationCallbacks* pAllocator)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['pipelineCache']
    std::unique_lock<std::mutex> lock(global_lock);
    uint64_t local_pipelineCache = reinterpret_cast<uint64_t &>(pipelineCache);
    pipelineCache = (VkPipelineCache)my_map_data->unique_id_mapping[local_pipelineCache];
    my_map_data->unique_id_mapping.erase(local_pipelineCache);
    lock.unlock();
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyPipelineCache(device, pipelineCache, pAllocator);
}


VKAPI_ATTR VkResult VKAPI_CALL GetPipelineCacheData(VkDevice device, VkPipelineCache pipelineCache, size_t* pDataSize, void* pData)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['pipelineCache']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    pipelineCache = (VkPipelineCache)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(pipelineCache)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->GetPipelineCacheData(device, pipelineCache, pDataSize, pData);
    return result;
}


VKAPI_ATTR VkResult VKAPI_CALL MergePipelineCaches(VkDevice device, VkPipelineCache dstCache, uint32_t srcCacheCount, const VkPipelineCache* pSrcCaches)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['dstCache', 'pSrcCaches[srcCacheCount]']
//LOCAL DECLS:['pSrcCaches']
    VkPipelineCache* local_pSrcCaches = NULL;
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    dstCache = (VkPipelineCache)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(dstCache)];
    if (pSrcCaches) {
        local_pSrcCaches = new VkPipelineCache[srcCacheCount];
        for (uint32_t idx0=0; idx0<srcCacheCount; ++idx0) {
            local_pSrcCaches[idx0] = (VkPipelineCache)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pSrcCaches[idx0])];
        }
    }
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->MergePipelineCaches(device, dstCache, srcCacheCount, (const VkPipelineCache*)local_pSrcCaches);
    if (local_pSrcCaches)
        delete[] local_pSrcCaches;
    return result;
}


VKAPI_ATTR VkResult VKAPI_CALL CreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines)
{
    return explicit_CreateGraphicsPipelines(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
}

VKAPI_ATTR VkResult VKAPI_CALL CreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkComputePipelineCreateInfo* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkPipeline* pPipelines)
{
    return explicit_CreateComputePipelines(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines);
}

VKAPI_ATTR void VKAPI_CALL DestroyPipeline(VkDevice device, VkPipeline pipeline, const VkAllocationCallbacks* pAllocator)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['pipeline']
    std::unique_lock<std::mutex> lock(global_lock);
    uint64_t local_pipeline = reinterpret_cast<uint64_t &>(pipeline);
    pipeline = (VkPipeline)my_map_data->unique_id_mapping[local_pipeline];
    my_map_data->unique_id_mapping.erase(local_pipeline);
    lock.unlock();
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyPipeline(device, pipeline, pAllocator);
}


VKAPI_ATTR VkResult VKAPI_CALL CreatePipelineLayout(VkDevice device, const VkPipelineLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkPipelineLayout* pPipelineLayout)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['pCreateInfo']
//LOCAL DECLS:['pCreateInfo']
    safe_VkPipelineLayoutCreateInfo* local_pCreateInfo = NULL;
    {
    std::lock_guard<std::mutex> lock(global_lock);
    if (pCreateInfo) {
        local_pCreateInfo = new safe_VkPipelineLayoutCreateInfo(pCreateInfo);
        if (local_pCreateInfo->pSetLayouts) {
            for (uint32_t idx0=0; idx0<pCreateInfo->setLayoutCount; ++idx0) {
                local_pCreateInfo->pSetLayouts[idx0] = (VkDescriptorSetLayout)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pCreateInfo->pSetLayouts[idx0])];
            }
        }
    }
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreatePipelineLayout(device, (const VkPipelineLayoutCreateInfo*)local_pCreateInfo, pAllocator, pPipelineLayout);
    if (local_pCreateInfo)
        delete local_pCreateInfo;
    if (VK_SUCCESS == result) {
        std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #961
        uint64_t unique_id = global_unique_id++;
        my_map_data->unique_id_mapping[unique_id] = reinterpret_cast<uint64_t &>(*pPipelineLayout);
        *pPipelineLayout = reinterpret_cast<VkPipelineLayout&>(unique_id);
    }
    return result;
}


VKAPI_ATTR void VKAPI_CALL DestroyPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout, const VkAllocationCallbacks* pAllocator)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['pipelineLayout']
    std::unique_lock<std::mutex> lock(global_lock);
    uint64_t local_pipelineLayout = reinterpret_cast<uint64_t &>(pipelineLayout);
    pipelineLayout = (VkPipelineLayout)my_map_data->unique_id_mapping[local_pipelineLayout];
    my_map_data->unique_id_mapping.erase(local_pipelineLayout);
    lock.unlock();
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyPipelineLayout(device, pipelineLayout, pAllocator);
}


VKAPI_ATTR VkResult VKAPI_CALL CreateSampler(VkDevice device, const VkSamplerCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSampler* pSampler)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateSampler(device, pCreateInfo, pAllocator, pSampler);
    if (VK_SUCCESS == result) {
        std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #961
        uint64_t unique_id = global_unique_id++;
        my_map_data->unique_id_mapping[unique_id] = reinterpret_cast<uint64_t &>(*pSampler);
        *pSampler = reinterpret_cast<VkSampler&>(unique_id);
    }
    return result;
}


VKAPI_ATTR void VKAPI_CALL DestroySampler(VkDevice device, VkSampler sampler, const VkAllocationCallbacks* pAllocator)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['sampler']
    std::unique_lock<std::mutex> lock(global_lock);
    uint64_t local_sampler = reinterpret_cast<uint64_t &>(sampler);
    sampler = (VkSampler)my_map_data->unique_id_mapping[local_sampler];
    my_map_data->unique_id_mapping.erase(local_sampler);
    lock.unlock();
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, device)->DestroySampler(device, sampler, pAllocator);
}


VKAPI_ATTR VkResult VKAPI_CALL CreateDescriptorSetLayout(VkDevice device, const VkDescriptorSetLayoutCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorSetLayout* pSetLayout)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['pCreateInfo']
//LOCAL DECLS:['pCreateInfo']
    safe_VkDescriptorSetLayoutCreateInfo* local_pCreateInfo = NULL;
    {
    std::lock_guard<std::mutex> lock(global_lock);
    if (pCreateInfo) {
        local_pCreateInfo = new safe_VkDescriptorSetLayoutCreateInfo(pCreateInfo);
        if (local_pCreateInfo->pBindings) {
            for (uint32_t idx0=0; idx0<pCreateInfo->bindingCount; ++idx0) {
                if (local_pCreateInfo->pBindings[idx0].pImmutableSamplers) {
                    for (uint32_t idx1=0; idx1<pCreateInfo->pBindings[idx0].descriptorCount; ++idx1) {
                        local_pCreateInfo->pBindings[idx0].pImmutableSamplers[idx1] = (VkSampler)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pCreateInfo->pBindings[idx0].pImmutableSamplers[idx1])];
                    }
                }
            }
        }
    }
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateDescriptorSetLayout(device, (const VkDescriptorSetLayoutCreateInfo*)local_pCreateInfo, pAllocator, pSetLayout);
    if (local_pCreateInfo)
        delete local_pCreateInfo;
    if (VK_SUCCESS == result) {
        std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #961
        uint64_t unique_id = global_unique_id++;
        my_map_data->unique_id_mapping[unique_id] = reinterpret_cast<uint64_t &>(*pSetLayout);
        *pSetLayout = reinterpret_cast<VkDescriptorSetLayout&>(unique_id);
    }
    return result;
}


VKAPI_ATTR void VKAPI_CALL DestroyDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout, const VkAllocationCallbacks* pAllocator)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['descriptorSetLayout']
    std::unique_lock<std::mutex> lock(global_lock);
    uint64_t local_descriptorSetLayout = reinterpret_cast<uint64_t &>(descriptorSetLayout);
    descriptorSetLayout = (VkDescriptorSetLayout)my_map_data->unique_id_mapping[local_descriptorSetLayout];
    my_map_data->unique_id_mapping.erase(local_descriptorSetLayout);
    lock.unlock();
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyDescriptorSetLayout(device, descriptorSetLayout, pAllocator);
}


VKAPI_ATTR VkResult VKAPI_CALL CreateDescriptorPool(VkDevice device, const VkDescriptorPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDescriptorPool* pDescriptorPool)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateDescriptorPool(device, pCreateInfo, pAllocator, pDescriptorPool);
    if (VK_SUCCESS == result) {
        std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #961
        uint64_t unique_id = global_unique_id++;
        my_map_data->unique_id_mapping[unique_id] = reinterpret_cast<uint64_t &>(*pDescriptorPool);
        *pDescriptorPool = reinterpret_cast<VkDescriptorPool&>(unique_id);
    }
    return result;
}


VKAPI_ATTR void VKAPI_CALL DestroyDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, const VkAllocationCallbacks* pAllocator)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['descriptorPool']
    std::unique_lock<std::mutex> lock(global_lock);
    uint64_t local_descriptorPool = reinterpret_cast<uint64_t &>(descriptorPool);
    descriptorPool = (VkDescriptorPool)my_map_data->unique_id_mapping[local_descriptorPool];
    my_map_data->unique_id_mapping.erase(local_descriptorPool);
    lock.unlock();
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyDescriptorPool(device, descriptorPool, pAllocator);
}


VKAPI_ATTR VkResult VKAPI_CALL ResetDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, VkDescriptorPoolResetFlags flags)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['descriptorPool']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    descriptorPool = (VkDescriptorPool)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(descriptorPool)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->ResetDescriptorPool(device, descriptorPool, flags);
    return result;
}


VKAPI_ATTR VkResult VKAPI_CALL AllocateDescriptorSets(VkDevice device, const VkDescriptorSetAllocateInfo* pAllocateInfo, VkDescriptorSet* pDescriptorSets)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['pAllocateInfo']
//LOCAL DECLS:['pAllocateInfo']
    safe_VkDescriptorSetAllocateInfo* local_pAllocateInfo = NULL;
    {
    std::lock_guard<std::mutex> lock(global_lock);
    if (pAllocateInfo) {
        local_pAllocateInfo = new safe_VkDescriptorSetAllocateInfo(pAllocateInfo);
// CODEGEN : file ../vk-layer-generate.py line #842
        local_pAllocateInfo->descriptorPool = (VkDescriptorPool)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pAllocateInfo->descriptorPool)];
        if (local_pAllocateInfo->pSetLayouts) {
            for (uint32_t idx0=0; idx0<pAllocateInfo->descriptorSetCount; ++idx0) {
                local_pAllocateInfo->pSetLayouts[idx0] = (VkDescriptorSetLayout)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pAllocateInfo->pSetLayouts[idx0])];
            }
        }
    }
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->AllocateDescriptorSets(device, (const VkDescriptorSetAllocateInfo*)local_pAllocateInfo, pDescriptorSets);
    if (local_pAllocateInfo)
        delete local_pAllocateInfo;
    if (VK_SUCCESS == result) {
        std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #951
        for (uint32_t i=0; i<pAllocateInfo->descriptorSetCount; ++i) {
            uint64_t unique_id = global_unique_id++;
            my_map_data->unique_id_mapping[unique_id] = reinterpret_cast<uint64_t &>(pDescriptorSets[i]);
            pDescriptorSets[i] = reinterpret_cast<VkDescriptorSet&>(unique_id);
        }
    }
    return result;
}


VKAPI_ATTR VkResult VKAPI_CALL FreeDescriptorSets(VkDevice device, VkDescriptorPool descriptorPool, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['descriptorPool', 'pDescriptorSets[descriptorSetCount]']
//LOCAL DECLS:['pDescriptorSets']
    VkDescriptorSet* local_pDescriptorSets = NULL;
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    descriptorPool = (VkDescriptorPool)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(descriptorPool)];
    if (pDescriptorSets) {
        local_pDescriptorSets = new VkDescriptorSet[descriptorSetCount];
        for (uint32_t idx0=0; idx0<descriptorSetCount; ++idx0) {
            local_pDescriptorSets[idx0] = (VkDescriptorSet)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pDescriptorSets[idx0])];
        }
    }
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->FreeDescriptorSets(device, descriptorPool, descriptorSetCount, (const VkDescriptorSet*)local_pDescriptorSets);
    if (local_pDescriptorSets)
        delete[] local_pDescriptorSets;
    return result;
}


VKAPI_ATTR void VKAPI_CALL UpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount, const VkWriteDescriptorSet* pDescriptorWrites, uint32_t descriptorCopyCount, const VkCopyDescriptorSet* pDescriptorCopies)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['pDescriptorCopies[descriptorCopyCount]', 'pDescriptorWrites[descriptorWriteCount]']
//LOCAL DECLS:['pDescriptorCopies', 'pDescriptorWrites']
    safe_VkCopyDescriptorSet* local_pDescriptorCopies = NULL;
    safe_VkWriteDescriptorSet* local_pDescriptorWrites = NULL;
    {
    std::lock_guard<std::mutex> lock(global_lock);
    if (pDescriptorCopies) {
        local_pDescriptorCopies = new safe_VkCopyDescriptorSet[descriptorCopyCount];
        for (uint32_t idx0=0; idx0<descriptorCopyCount; ++idx0) {
            local_pDescriptorCopies[idx0].initialize(&pDescriptorCopies[idx0]);
            if (pDescriptorCopies[idx0].dstSet) {
                local_pDescriptorCopies[idx0].dstSet = (VkDescriptorSet)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pDescriptorCopies[idx0].dstSet)];
            }
            if (pDescriptorCopies[idx0].srcSet) {
                local_pDescriptorCopies[idx0].srcSet = (VkDescriptorSet)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pDescriptorCopies[idx0].srcSet)];
            }
        }
    }
    if (pDescriptorWrites) {
        local_pDescriptorWrites = new safe_VkWriteDescriptorSet[descriptorWriteCount];
        for (uint32_t idx1=0; idx1<descriptorWriteCount; ++idx1) {
            local_pDescriptorWrites[idx1].initialize(&pDescriptorWrites[idx1]);
            if (pDescriptorWrites[idx1].dstSet) {
                local_pDescriptorWrites[idx1].dstSet = (VkDescriptorSet)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pDescriptorWrites[idx1].dstSet)];
            }
            if (local_pDescriptorWrites[idx1].pBufferInfo) {
                for (uint32_t idx2=0; idx2<pDescriptorWrites[idx1].descriptorCount; ++idx2) {
                    if (pDescriptorWrites[idx1].pBufferInfo[idx2].buffer) {
                        local_pDescriptorWrites[idx1].pBufferInfo[idx2].buffer = (VkBuffer)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pDescriptorWrites[idx1].pBufferInfo[idx2].buffer)];
                    }
                }
            }
            if (local_pDescriptorWrites[idx1].pImageInfo) {
                for (uint32_t idx3=0; idx3<pDescriptorWrites[idx1].descriptorCount; ++idx3) {
                    if (pDescriptorWrites[idx1].pImageInfo[idx3].imageView) {
                        local_pDescriptorWrites[idx1].pImageInfo[idx3].imageView = (VkImageView)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pDescriptorWrites[idx1].pImageInfo[idx3].imageView)];
                    }
                    if (pDescriptorWrites[idx1].pImageInfo[idx3].sampler) {
                        local_pDescriptorWrites[idx1].pImageInfo[idx3].sampler = (VkSampler)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pDescriptorWrites[idx1].pImageInfo[idx3].sampler)];
                    }
                }
            }
            if (local_pDescriptorWrites[idx1].pTexelBufferView) {
                for (uint32_t idx4=0; idx4<pDescriptorWrites[idx1].descriptorCount; ++idx4) {
                    local_pDescriptorWrites[idx1].pTexelBufferView[idx4] = (VkBufferView)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pDescriptorWrites[idx1].pTexelBufferView[idx4])];
                }
            }
        }
    }
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, device)->UpdateDescriptorSets(device, descriptorWriteCount, (const VkWriteDescriptorSet*)local_pDescriptorWrites, descriptorCopyCount, (const VkCopyDescriptorSet*)local_pDescriptorCopies);
    if (local_pDescriptorCopies)
        delete[] local_pDescriptorCopies;
    if (local_pDescriptorWrites)
        delete[] local_pDescriptorWrites;
}


VKAPI_ATTR VkResult VKAPI_CALL CreateFramebuffer(VkDevice device, const VkFramebufferCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkFramebuffer* pFramebuffer)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['pCreateInfo']
//LOCAL DECLS:['pCreateInfo']
    safe_VkFramebufferCreateInfo* local_pCreateInfo = NULL;
    {
    std::lock_guard<std::mutex> lock(global_lock);
    if (pCreateInfo) {
        local_pCreateInfo = new safe_VkFramebufferCreateInfo(pCreateInfo);
        if (local_pCreateInfo->pAttachments) {
            for (uint32_t idx0=0; idx0<pCreateInfo->attachmentCount; ++idx0) {
                local_pCreateInfo->pAttachments[idx0] = (VkImageView)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pCreateInfo->pAttachments[idx0])];
            }
        }
        if (pCreateInfo->renderPass) {
            local_pCreateInfo->renderPass = (VkRenderPass)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pCreateInfo->renderPass)];
        }
    }
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateFramebuffer(device, (const VkFramebufferCreateInfo*)local_pCreateInfo, pAllocator, pFramebuffer);
    if (local_pCreateInfo)
        delete local_pCreateInfo;
    if (VK_SUCCESS == result) {
        std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #961
        uint64_t unique_id = global_unique_id++;
        my_map_data->unique_id_mapping[unique_id] = reinterpret_cast<uint64_t &>(*pFramebuffer);
        *pFramebuffer = reinterpret_cast<VkFramebuffer&>(unique_id);
    }
    return result;
}


VKAPI_ATTR void VKAPI_CALL DestroyFramebuffer(VkDevice device, VkFramebuffer framebuffer, const VkAllocationCallbacks* pAllocator)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['framebuffer']
    std::unique_lock<std::mutex> lock(global_lock);
    uint64_t local_framebuffer = reinterpret_cast<uint64_t &>(framebuffer);
    framebuffer = (VkFramebuffer)my_map_data->unique_id_mapping[local_framebuffer];
    my_map_data->unique_id_mapping.erase(local_framebuffer);
    lock.unlock();
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyFramebuffer(device, framebuffer, pAllocator);
}


VKAPI_ATTR VkResult VKAPI_CALL CreateRenderPass(VkDevice device, const VkRenderPassCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkRenderPass* pRenderPass)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateRenderPass(device, pCreateInfo, pAllocator, pRenderPass);
    if (VK_SUCCESS == result) {
        std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #961
        uint64_t unique_id = global_unique_id++;
        my_map_data->unique_id_mapping[unique_id] = reinterpret_cast<uint64_t &>(*pRenderPass);
        *pRenderPass = reinterpret_cast<VkRenderPass&>(unique_id);
    }
    return result;
}


VKAPI_ATTR void VKAPI_CALL DestroyRenderPass(VkDevice device, VkRenderPass renderPass, const VkAllocationCallbacks* pAllocator)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['renderPass']
    std::unique_lock<std::mutex> lock(global_lock);
    uint64_t local_renderPass = reinterpret_cast<uint64_t &>(renderPass);
    renderPass = (VkRenderPass)my_map_data->unique_id_mapping[local_renderPass];
    my_map_data->unique_id_mapping.erase(local_renderPass);
    lock.unlock();
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyRenderPass(device, renderPass, pAllocator);
}


VKAPI_ATTR void VKAPI_CALL GetRenderAreaGranularity(VkDevice device, VkRenderPass renderPass, VkExtent2D* pGranularity)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['renderPass']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    renderPass = (VkRenderPass)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(renderPass)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, device)->GetRenderAreaGranularity(device, renderPass, pGranularity);
}


VKAPI_ATTR VkResult VKAPI_CALL CreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkCommandPool* pCommandPool)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateCommandPool(device, pCreateInfo, pAllocator, pCommandPool);
    if (VK_SUCCESS == result) {
        std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #961
        uint64_t unique_id = global_unique_id++;
        my_map_data->unique_id_mapping[unique_id] = reinterpret_cast<uint64_t &>(*pCommandPool);
        *pCommandPool = reinterpret_cast<VkCommandPool&>(unique_id);
    }
    return result;
}


VKAPI_ATTR void VKAPI_CALL DestroyCommandPool(VkDevice device, VkCommandPool commandPool, const VkAllocationCallbacks* pAllocator)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['commandPool']
    std::unique_lock<std::mutex> lock(global_lock);
    uint64_t local_commandPool = reinterpret_cast<uint64_t &>(commandPool);
    commandPool = (VkCommandPool)my_map_data->unique_id_mapping[local_commandPool];
    my_map_data->unique_id_mapping.erase(local_commandPool);
    lock.unlock();
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, device)->DestroyCommandPool(device, commandPool, pAllocator);
}


VKAPI_ATTR VkResult VKAPI_CALL ResetCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolResetFlags flags)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['commandPool']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    commandPool = (VkCommandPool)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(commandPool)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->ResetCommandPool(device, commandPool, flags);
    return result;
}


VKAPI_ATTR VkResult VKAPI_CALL AllocateCommandBuffers(VkDevice device, const VkCommandBufferAllocateInfo* pAllocateInfo, VkCommandBuffer* pCommandBuffers)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['pAllocateInfo']
//LOCAL DECLS:['pAllocateInfo']
    safe_VkCommandBufferAllocateInfo* local_pAllocateInfo = NULL;
    {
    std::lock_guard<std::mutex> lock(global_lock);
    if (pAllocateInfo) {
        local_pAllocateInfo = new safe_VkCommandBufferAllocateInfo(pAllocateInfo);
// CODEGEN : file ../vk-layer-generate.py line #842
        local_pAllocateInfo->commandPool = (VkCommandPool)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pAllocateInfo->commandPool)];
    }
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->AllocateCommandBuffers(device, (const VkCommandBufferAllocateInfo*)local_pAllocateInfo, pCommandBuffers);
    if (local_pAllocateInfo)
        delete local_pAllocateInfo;
    return result;
}


VKAPI_ATTR void VKAPI_CALL FreeCommandBuffers(VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, const VkCommandBuffer* pCommandBuffers)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['commandPool']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    commandPool = (VkCommandPool)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(commandPool)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, device)->FreeCommandBuffers(device, commandPool, commandBufferCount, pCommandBuffers);
}


VKAPI_ATTR VkResult VKAPI_CALL BeginCommandBuffer(VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo* pBeginInfo)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(commandBuffer), layer_data_map);
// STRUCT USES:['pBeginInfo']
//LOCAL DECLS:['pBeginInfo']
    safe_VkCommandBufferBeginInfo* local_pBeginInfo = NULL;
    {
    std::lock_guard<std::mutex> lock(global_lock);
    if (pBeginInfo) {
        local_pBeginInfo = new safe_VkCommandBufferBeginInfo(pBeginInfo);
        if (local_pBeginInfo->pInheritanceInfo) {
// CODEGEN : file ../vk-layer-generate.py line #842
            local_pBeginInfo->pInheritanceInfo->framebuffer = (VkFramebuffer)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pBeginInfo->pInheritanceInfo->framebuffer)];
// CODEGEN : file ../vk-layer-generate.py line #842
            local_pBeginInfo->pInheritanceInfo->renderPass = (VkRenderPass)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pBeginInfo->pInheritanceInfo->renderPass)];
        }
    }
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, commandBuffer)->BeginCommandBuffer(commandBuffer, (const VkCommandBufferBeginInfo*)local_pBeginInfo);
    if (local_pBeginInfo)
        delete local_pBeginInfo;
    return result;
}


VKAPI_ATTR void VKAPI_CALL CmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(commandBuffer), layer_data_map);
// STRUCT USES:['pipeline']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    pipeline = (VkPipeline)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(pipeline)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdBindPipeline(commandBuffer, pipelineBindPoint, pipeline);
}


VKAPI_ATTR void VKAPI_CALL CmdBindDescriptorSets(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const VkDescriptorSet* pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t* pDynamicOffsets)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(commandBuffer), layer_data_map);
// STRUCT USES:['layout', 'pDescriptorSets[descriptorSetCount]']
//LOCAL DECLS:['pDescriptorSets']
    VkDescriptorSet* local_pDescriptorSets = NULL;
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    layout = (VkPipelineLayout)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(layout)];
    if (pDescriptorSets) {
        local_pDescriptorSets = new VkDescriptorSet[descriptorSetCount];
        for (uint32_t idx0=0; idx0<descriptorSetCount; ++idx0) {
            local_pDescriptorSets[idx0] = (VkDescriptorSet)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pDescriptorSets[idx0])];
        }
    }
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdBindDescriptorSets(commandBuffer, pipelineBindPoint, layout, firstSet, descriptorSetCount, (const VkDescriptorSet*)local_pDescriptorSets, dynamicOffsetCount, pDynamicOffsets);
    if (local_pDescriptorSets)
        delete[] local_pDescriptorSets;
}


VKAPI_ATTR void VKAPI_CALL CmdBindIndexBuffer(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(commandBuffer), layer_data_map);
// STRUCT USES:['buffer']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    buffer = (VkBuffer)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(buffer)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdBindIndexBuffer(commandBuffer, buffer, offset, indexType);
}


VKAPI_ATTR void VKAPI_CALL CmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer* pBuffers, const VkDeviceSize* pOffsets)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(commandBuffer), layer_data_map);
// STRUCT USES:['pBuffers[bindingCount]']
//LOCAL DECLS:['pBuffers']
    VkBuffer* local_pBuffers = NULL;
    {
    std::lock_guard<std::mutex> lock(global_lock);
    if (pBuffers) {
        local_pBuffers = new VkBuffer[bindingCount];
        for (uint32_t idx0=0; idx0<bindingCount; ++idx0) {
            local_pBuffers[idx0] = (VkBuffer)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pBuffers[idx0])];
        }
    }
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdBindVertexBuffers(commandBuffer, firstBinding, bindingCount, (const VkBuffer*)local_pBuffers, pOffsets);
    if (local_pBuffers)
        delete[] local_pBuffers;
}


VKAPI_ATTR void VKAPI_CALL CmdDrawIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(commandBuffer), layer_data_map);
// STRUCT USES:['buffer']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    buffer = (VkBuffer)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(buffer)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdDrawIndirect(commandBuffer, buffer, offset, drawCount, stride);
}


VKAPI_ATTR void VKAPI_CALL CmdDrawIndexedIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(commandBuffer), layer_data_map);
// STRUCT USES:['buffer']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    buffer = (VkBuffer)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(buffer)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdDrawIndexedIndirect(commandBuffer, buffer, offset, drawCount, stride);
}


VKAPI_ATTR void VKAPI_CALL CmdDispatchIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(commandBuffer), layer_data_map);
// STRUCT USES:['buffer']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    buffer = (VkBuffer)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(buffer)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdDispatchIndirect(commandBuffer, buffer, offset);
}


VKAPI_ATTR void VKAPI_CALL CmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferCopy* pRegions)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(commandBuffer), layer_data_map);
// STRUCT USES:['dstBuffer', 'srcBuffer']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    dstBuffer = (VkBuffer)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(dstBuffer)];
// CODEGEN : file ../vk-layer-generate.py line #842
    srcBuffer = (VkBuffer)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(srcBuffer)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, regionCount, pRegions);
}


VKAPI_ATTR void VKAPI_CALL CmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageCopy* pRegions)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(commandBuffer), layer_data_map);
// STRUCT USES:['dstImage', 'srcImage']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    dstImage = (VkImage)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(dstImage)];
// CODEGEN : file ../vk-layer-generate.py line #842
    srcImage = (VkImage)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(srcImage)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdCopyImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
}


VKAPI_ATTR void VKAPI_CALL CmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageBlit* pRegions, VkFilter filter)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(commandBuffer), layer_data_map);
// STRUCT USES:['dstImage', 'srcImage']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    dstImage = (VkImage)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(dstImage)];
// CODEGEN : file ../vk-layer-generate.py line #842
    srcImage = (VkImage)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(srcImage)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdBlitImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions, filter);
}


VKAPI_ATTR void VKAPI_CALL CmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy* pRegions)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(commandBuffer), layer_data_map);
// STRUCT USES:['dstImage', 'srcBuffer']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    dstImage = (VkImage)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(dstImage)];
// CODEGEN : file ../vk-layer-generate.py line #842
    srcBuffer = (VkBuffer)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(srcBuffer)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdCopyBufferToImage(commandBuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions);
}


VKAPI_ATTR void VKAPI_CALL CmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy* pRegions)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(commandBuffer), layer_data_map);
// STRUCT USES:['dstBuffer', 'srcImage']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    dstBuffer = (VkBuffer)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(dstBuffer)];
// CODEGEN : file ../vk-layer-generate.py line #842
    srcImage = (VkImage)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(srcImage)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdCopyImageToBuffer(commandBuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions);
}


VKAPI_ATTR void VKAPI_CALL CmdUpdateBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, const void* pData)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(commandBuffer), layer_data_map);
// STRUCT USES:['dstBuffer']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    dstBuffer = (VkBuffer)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(dstBuffer)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdUpdateBuffer(commandBuffer, dstBuffer, dstOffset, dataSize, pData);
}


VKAPI_ATTR void VKAPI_CALL CmdFillBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(commandBuffer), layer_data_map);
// STRUCT USES:['dstBuffer']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    dstBuffer = (VkBuffer)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(dstBuffer)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdFillBuffer(commandBuffer, dstBuffer, dstOffset, size, data);
}


VKAPI_ATTR void VKAPI_CALL CmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearColorValue* pColor, uint32_t rangeCount, const VkImageSubresourceRange* pRanges)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(commandBuffer), layer_data_map);
// STRUCT USES:['image']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    image = (VkImage)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(image)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdClearColorImage(commandBuffer, image, imageLayout, pColor, rangeCount, pRanges);
}


VKAPI_ATTR void VKAPI_CALL CmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearDepthStencilValue* pDepthStencil, uint32_t rangeCount, const VkImageSubresourceRange* pRanges)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(commandBuffer), layer_data_map);
// STRUCT USES:['image']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    image = (VkImage)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(image)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdClearDepthStencilImage(commandBuffer, image, imageLayout, pDepthStencil, rangeCount, pRanges);
}


VKAPI_ATTR void VKAPI_CALL CmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageResolve* pRegions)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(commandBuffer), layer_data_map);
// STRUCT USES:['dstImage', 'srcImage']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    dstImage = (VkImage)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(dstImage)];
// CODEGEN : file ../vk-layer-generate.py line #842
    srcImage = (VkImage)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(srcImage)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdResolveImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions);
}


VKAPI_ATTR void VKAPI_CALL CmdSetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(commandBuffer), layer_data_map);
// STRUCT USES:['event']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    event = (VkEvent)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(event)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdSetEvent(commandBuffer, event, stageMask);
}


VKAPI_ATTR void VKAPI_CALL CmdResetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(commandBuffer), layer_data_map);
// STRUCT USES:['event']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    event = (VkEvent)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(event)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdResetEvent(commandBuffer, event, stageMask);
}


VKAPI_ATTR void VKAPI_CALL CmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent* pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(commandBuffer), layer_data_map);
// STRUCT USES:['pBufferMemoryBarriers[bufferMemoryBarrierCount]', 'pEvents[eventCount]', 'pImageMemoryBarriers[imageMemoryBarrierCount]']
//LOCAL DECLS:['pBufferMemoryBarriers', 'pEvents', 'pImageMemoryBarriers']
    VkEvent* local_pEvents = NULL;
    safe_VkBufferMemoryBarrier* local_pBufferMemoryBarriers = NULL;
    safe_VkImageMemoryBarrier* local_pImageMemoryBarriers = NULL;
    {
    std::lock_guard<std::mutex> lock(global_lock);
    if (pBufferMemoryBarriers) {
        local_pBufferMemoryBarriers = new safe_VkBufferMemoryBarrier[bufferMemoryBarrierCount];
        for (uint32_t idx0=0; idx0<bufferMemoryBarrierCount; ++idx0) {
            local_pBufferMemoryBarriers[idx0].initialize(&pBufferMemoryBarriers[idx0]);
            if (pBufferMemoryBarriers[idx0].buffer) {
                local_pBufferMemoryBarriers[idx0].buffer = (VkBuffer)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pBufferMemoryBarriers[idx0].buffer)];
            }
        }
    }
    if (pEvents) {
        local_pEvents = new VkEvent[eventCount];
        for (uint32_t idx1=0; idx1<eventCount; ++idx1) {
            local_pEvents[idx1] = (VkEvent)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pEvents[idx1])];
        }
    }
    if (pImageMemoryBarriers) {
        local_pImageMemoryBarriers = new safe_VkImageMemoryBarrier[imageMemoryBarrierCount];
        for (uint32_t idx2=0; idx2<imageMemoryBarrierCount; ++idx2) {
            local_pImageMemoryBarriers[idx2].initialize(&pImageMemoryBarriers[idx2]);
            if (pImageMemoryBarriers[idx2].image) {
                local_pImageMemoryBarriers[idx2].image = (VkImage)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pImageMemoryBarriers[idx2].image)];
            }
        }
    }
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdWaitEvents(commandBuffer, eventCount, (const VkEvent*)local_pEvents, srcStageMask, dstStageMask, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, (const VkBufferMemoryBarrier*)local_pBufferMemoryBarriers, imageMemoryBarrierCount, (const VkImageMemoryBarrier*)local_pImageMemoryBarriers);
    if (local_pBufferMemoryBarriers)
        delete[] local_pBufferMemoryBarriers;
    if (local_pEvents)
        delete[] local_pEvents;
    if (local_pImageMemoryBarriers)
        delete[] local_pImageMemoryBarriers;
}


VKAPI_ATTR void VKAPI_CALL CmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(commandBuffer), layer_data_map);
// STRUCT USES:['pBufferMemoryBarriers[bufferMemoryBarrierCount]', 'pImageMemoryBarriers[imageMemoryBarrierCount]']
//LOCAL DECLS:['pBufferMemoryBarriers', 'pImageMemoryBarriers']
    safe_VkBufferMemoryBarrier* local_pBufferMemoryBarriers = NULL;
    safe_VkImageMemoryBarrier* local_pImageMemoryBarriers = NULL;
    {
    std::lock_guard<std::mutex> lock(global_lock);
    if (pBufferMemoryBarriers) {
        local_pBufferMemoryBarriers = new safe_VkBufferMemoryBarrier[bufferMemoryBarrierCount];
        for (uint32_t idx0=0; idx0<bufferMemoryBarrierCount; ++idx0) {
            local_pBufferMemoryBarriers[idx0].initialize(&pBufferMemoryBarriers[idx0]);
            if (pBufferMemoryBarriers[idx0].buffer) {
                local_pBufferMemoryBarriers[idx0].buffer = (VkBuffer)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pBufferMemoryBarriers[idx0].buffer)];
            }
        }
    }
    if (pImageMemoryBarriers) {
        local_pImageMemoryBarriers = new safe_VkImageMemoryBarrier[imageMemoryBarrierCount];
        for (uint32_t idx1=0; idx1<imageMemoryBarrierCount; ++idx1) {
            local_pImageMemoryBarriers[idx1].initialize(&pImageMemoryBarriers[idx1]);
            if (pImageMemoryBarriers[idx1].image) {
                local_pImageMemoryBarriers[idx1].image = (VkImage)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pImageMemoryBarriers[idx1].image)];
            }
        }
    }
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdPipelineBarrier(commandBuffer, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, (const VkBufferMemoryBarrier*)local_pBufferMemoryBarriers, imageMemoryBarrierCount, (const VkImageMemoryBarrier*)local_pImageMemoryBarriers);
    if (local_pBufferMemoryBarriers)
        delete[] local_pBufferMemoryBarriers;
    if (local_pImageMemoryBarriers)
        delete[] local_pImageMemoryBarriers;
}


VKAPI_ATTR void VKAPI_CALL CmdBeginQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(commandBuffer), layer_data_map);
// STRUCT USES:['queryPool']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    queryPool = (VkQueryPool)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(queryPool)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdBeginQuery(commandBuffer, queryPool, query, flags);
}


VKAPI_ATTR void VKAPI_CALL CmdEndQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(commandBuffer), layer_data_map);
// STRUCT USES:['queryPool']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    queryPool = (VkQueryPool)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(queryPool)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdEndQuery(commandBuffer, queryPool, query);
}


VKAPI_ATTR void VKAPI_CALL CmdResetQueryPool(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(commandBuffer), layer_data_map);
// STRUCT USES:['queryPool']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    queryPool = (VkQueryPool)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(queryPool)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdResetQueryPool(commandBuffer, queryPool, firstQuery, queryCount);
}


VKAPI_ATTR void VKAPI_CALL CmdWriteTimestamp(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, uint32_t query)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(commandBuffer), layer_data_map);
// STRUCT USES:['queryPool']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    queryPool = (VkQueryPool)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(queryPool)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdWriteTimestamp(commandBuffer, pipelineStage, queryPool, query);
}


VKAPI_ATTR void VKAPI_CALL CmdCopyQueryPoolResults(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize stride, VkQueryResultFlags flags)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(commandBuffer), layer_data_map);
// STRUCT USES:['dstBuffer', 'queryPool']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    dstBuffer = (VkBuffer)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(dstBuffer)];
// CODEGEN : file ../vk-layer-generate.py line #842
    queryPool = (VkQueryPool)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(queryPool)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdCopyQueryPoolResults(commandBuffer, queryPool, firstQuery, queryCount, dstBuffer, dstOffset, stride, flags);
}


VKAPI_ATTR void VKAPI_CALL CmdPushConstants(VkCommandBuffer commandBuffer, VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void* pValues)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(commandBuffer), layer_data_map);
// STRUCT USES:['layout']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    layout = (VkPipelineLayout)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(layout)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdPushConstants(commandBuffer, layout, stageFlags, offset, size, pValues);
}


VKAPI_ATTR void VKAPI_CALL CmdBeginRenderPass(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo* pRenderPassBegin, VkSubpassContents contents)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(commandBuffer), layer_data_map);
// STRUCT USES:['pRenderPassBegin']
//LOCAL DECLS:['pRenderPassBegin']
    safe_VkRenderPassBeginInfo* local_pRenderPassBegin = NULL;
    {
    std::lock_guard<std::mutex> lock(global_lock);
    if (pRenderPassBegin) {
        local_pRenderPassBegin = new safe_VkRenderPassBeginInfo(pRenderPassBegin);
// CODEGEN : file ../vk-layer-generate.py line #842
        local_pRenderPassBegin->framebuffer = (VkFramebuffer)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pRenderPassBegin->framebuffer)];
// CODEGEN : file ../vk-layer-generate.py line #842
        local_pRenderPassBegin->renderPass = (VkRenderPass)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pRenderPassBegin->renderPass)];
    }
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, commandBuffer)->CmdBeginRenderPass(commandBuffer, (const VkRenderPassBeginInfo*)local_pRenderPassBegin, contents);
    if (local_pRenderPassBegin)
        delete local_pRenderPassBegin;
}


VKAPI_ATTR void VKAPI_CALL DestroySurfaceKHR(VkInstance instance, VkSurfaceKHR surface, const VkAllocationCallbacks* pAllocator)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(instance), layer_data_map);
// STRUCT USES:['surface']
    std::unique_lock<std::mutex> lock(global_lock);
    uint64_t local_surface = reinterpret_cast<uint64_t &>(surface);
    surface = (VkSurfaceKHR)my_map_data->unique_id_mapping[local_surface];
    my_map_data->unique_id_mapping.erase(local_surface);
    lock.unlock();
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_instance_table_map, instance)->DestroySurfaceKHR(instance, surface, pAllocator);
}


VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceSurfaceSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, VkSurfaceKHR surface, VkBool32* pSupported)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(physicalDevice), layer_data_map);
// STRUCT USES:['surface']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    surface = (VkSurfaceKHR)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(surface)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_instance_table_map, physicalDevice)->GetPhysicalDeviceSurfaceSupportKHR(physicalDevice, queueFamilyIndex, surface, pSupported);
    return result;
}


VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceSurfaceCapabilitiesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilitiesKHR* pSurfaceCapabilities)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(physicalDevice), layer_data_map);
// STRUCT USES:['surface']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    surface = (VkSurfaceKHR)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(surface)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_instance_table_map, physicalDevice)->GetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, pSurfaceCapabilities);
    return result;
}


VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceSurfaceFormatsKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pSurfaceFormatCount, VkSurfaceFormatKHR* pSurfaceFormats)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(physicalDevice), layer_data_map);
// STRUCT USES:['surface']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    surface = (VkSurfaceKHR)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(surface)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_instance_table_map, physicalDevice)->GetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, pSurfaceFormatCount, pSurfaceFormats);
    return result;
}


VKAPI_ATTR VkResult VKAPI_CALL GetPhysicalDeviceSurfacePresentModesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t* pPresentModeCount, VkPresentModeKHR* pPresentModes)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(physicalDevice), layer_data_map);
// STRUCT USES:['surface']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    surface = (VkSurfaceKHR)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(surface)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_instance_table_map, physicalDevice)->GetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, pPresentModeCount, pPresentModes);
    return result;
}


VKAPI_ATTR VkResult VKAPI_CALL CreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchain)
{
    return explicit_CreateSwapchainKHR(device, pCreateInfo, pAllocator, pSwapchain);
}

VKAPI_ATTR void VKAPI_CALL DestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks* pAllocator)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['swapchain']
    std::unique_lock<std::mutex> lock(global_lock);
    uint64_t local_swapchain = reinterpret_cast<uint64_t &>(swapchain);
    swapchain = (VkSwapchainKHR)my_map_data->unique_id_mapping[local_swapchain];
    my_map_data->unique_id_mapping.erase(local_swapchain);
    lock.unlock();
// CODEGEN : file ../vk-layer-generate.py line #980
    get_dispatch_table(unique_objects_device_table_map, device)->DestroySwapchainKHR(device, swapchain, pAllocator);
}


VKAPI_ATTR VkResult VKAPI_CALL GetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain, uint32_t* pSwapchainImageCount, VkImage* pSwapchainImages)
{
    return explicit_GetSwapchainImagesKHR(device, swapchain, pSwapchainImageCount, pSwapchainImages);
}

VKAPI_ATTR VkResult VKAPI_CALL AcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t* pImageIndex)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['fence', 'semaphore', 'swapchain']
    {
    std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #842
    fence = (VkFence)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(fence)];
// CODEGEN : file ../vk-layer-generate.py line #842
    semaphore = (VkSemaphore)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(semaphore)];
// CODEGEN : file ../vk-layer-generate.py line #842
    swapchain = (VkSwapchainKHR)my_map_data->unique_id_mapping[reinterpret_cast<uint64_t &>(swapchain)];
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->AcquireNextImageKHR(device, swapchain, timeout, semaphore, fence, pImageIndex);
    return result;
}


VKAPI_ATTR VkResult VKAPI_CALL QueuePresentKHR(VkQueue queue, const VkPresentInfoKHR* pPresentInfo)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(queue), layer_data_map);
// STRUCT USES:['pPresentInfo']
//LOCAL DECLS:['pPresentInfo']
    safe_VkPresentInfoKHR* local_pPresentInfo = NULL;
    {
    std::lock_guard<std::mutex> lock(global_lock);
    if (pPresentInfo) {
        local_pPresentInfo = new safe_VkPresentInfoKHR(pPresentInfo);
        if (local_pPresentInfo->pSwapchains) {
            for (uint32_t idx0=0; idx0<pPresentInfo->swapchainCount; ++idx0) {
                local_pPresentInfo->pSwapchains[idx0] = (VkSwapchainKHR)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pPresentInfo->pSwapchains[idx0])];
            }
        }
        if (local_pPresentInfo->pWaitSemaphores) {
            for (uint32_t idx1=0; idx1<pPresentInfo->waitSemaphoreCount; ++idx1) {
                local_pPresentInfo->pWaitSemaphores[idx1] = (VkSemaphore)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pPresentInfo->pWaitSemaphores[idx1])];
            }
        }
    }
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, queue)->QueuePresentKHR(queue, (const VkPresentInfoKHR*)local_pPresentInfo);
    if (local_pPresentInfo)
        delete local_pPresentInfo;
    return result;
}


#ifdef VK_USE_PLATFORM_ANDROID_KHR
VKAPI_ATTR VkResult VKAPI_CALL CreateAndroidSurfaceKHR(VkInstance instance, const VkAndroidSurfaceCreateInfoKHR* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkSurfaceKHR* pSurface)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(instance), layer_data_map);
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_instance_table_map, instance)->CreateAndroidSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface);
    if (VK_SUCCESS == result) {
        std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #961
        uint64_t unique_id = global_unique_id++;
        my_map_data->unique_id_mapping[unique_id] = reinterpret_cast<uint64_t &>(*pSurface);
        *pSurface = reinterpret_cast<VkSurfaceKHR&>(unique_id);
    }
    return result;
}
#endif


VKAPI_ATTR VkResult VKAPI_CALL CreateSharedSwapchainsKHR(VkDevice device, uint32_t swapchainCount, const VkSwapchainCreateInfoKHR* pCreateInfos, const VkAllocationCallbacks* pAllocator, VkSwapchainKHR* pSwapchains)
{
// CODEGEN : file ../vk-layer-generate.py line #883
    layer_data *my_map_data = get_my_data_ptr(get_dispatch_key(device), layer_data_map);
// STRUCT USES:['pCreateInfos[swapchainCount]']
//LOCAL DECLS:['pCreateInfos']
    safe_VkSwapchainCreateInfoKHR* local_pCreateInfos = NULL;
    {
    std::lock_guard<std::mutex> lock(global_lock);
    if (pCreateInfos) {
        local_pCreateInfos = new safe_VkSwapchainCreateInfoKHR[swapchainCount];
        for (uint32_t idx0=0; idx0<swapchainCount; ++idx0) {
            local_pCreateInfos[idx0].initialize(&pCreateInfos[idx0]);
            if (pCreateInfos[idx0].oldSwapchain) {
                local_pCreateInfos[idx0].oldSwapchain = (VkSwapchainKHR)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pCreateInfos[idx0].oldSwapchain)];
            }
            if (pCreateInfos[idx0].surface) {
                local_pCreateInfos[idx0].surface = (VkSurfaceKHR)my_map_data->unique_id_mapping[reinterpret_cast<const uint64_t &>(pCreateInfos[idx0].surface)];
            }
        }
    }
    }
// CODEGEN : file ../vk-layer-generate.py line #980
    VkResult result = get_dispatch_table(unique_objects_device_table_map, device)->CreateSharedSwapchainsKHR(device, swapchainCount, (const VkSwapchainCreateInfoKHR*)local_pCreateInfos, pAllocator, pSwapchains);
    if (local_pCreateInfos)
        delete[] local_pCreateInfos;
    if (VK_SUCCESS == result) {
        std::lock_guard<std::mutex> lock(global_lock);
// CODEGEN : file ../vk-layer-generate.py line #961
        uint64_t unique_id = global_unique_id++;
        my_map_data->unique_id_mapping[unique_id] = reinterpret_cast<uint64_t &>(*pSwapchains);
        *pSwapchains = reinterpret_cast<VkSwapchainKHR&>(unique_id);
    }
    return result;
}


// CODEGEN : file ../vk-layer-generate.py line #468
static inline PFN_vkVoidFunction intercept_core_device_command(const char *name)
{
    if (!name || name[0] != 'v' || name[1] != 'k')
        return NULL;

    name += 2;
    if (!strcmp(name, "GetDeviceProcAddr"))
        return (PFN_vkVoidFunction) GetDeviceProcAddr;
    if (!strcmp(name, "DestroyDevice"))
        return (PFN_vkVoidFunction) DestroyDevice;
    if (!strcmp(name, "QueueSubmit"))
        return (PFN_vkVoidFunction) QueueSubmit;
    if (!strcmp(name, "AllocateMemory"))
        return (PFN_vkVoidFunction) AllocateMemory;
    if (!strcmp(name, "FreeMemory"))
        return (PFN_vkVoidFunction) FreeMemory;
    if (!strcmp(name, "MapMemory"))
        return (PFN_vkVoidFunction) MapMemory;
    if (!strcmp(name, "UnmapMemory"))
        return (PFN_vkVoidFunction) UnmapMemory;
    if (!strcmp(name, "FlushMappedMemoryRanges"))
        return (PFN_vkVoidFunction) FlushMappedMemoryRanges;
    if (!strcmp(name, "InvalidateMappedMemoryRanges"))
        return (PFN_vkVoidFunction) InvalidateMappedMemoryRanges;
    if (!strcmp(name, "GetDeviceMemoryCommitment"))
        return (PFN_vkVoidFunction) GetDeviceMemoryCommitment;
    if (!strcmp(name, "BindBufferMemory"))
        return (PFN_vkVoidFunction) BindBufferMemory;
    if (!strcmp(name, "BindImageMemory"))
        return (PFN_vkVoidFunction) BindImageMemory;
    if (!strcmp(name, "GetBufferMemoryRequirements"))
        return (PFN_vkVoidFunction) GetBufferMemoryRequirements;
    if (!strcmp(name, "GetImageMemoryRequirements"))
        return (PFN_vkVoidFunction) GetImageMemoryRequirements;
    if (!strcmp(name, "GetImageSparseMemoryRequirements"))
        return (PFN_vkVoidFunction) GetImageSparseMemoryRequirements;
    if (!strcmp(name, "QueueBindSparse"))
        return (PFN_vkVoidFunction) QueueBindSparse;
    if (!strcmp(name, "CreateFence"))
        return (PFN_vkVoidFunction) CreateFence;
    if (!strcmp(name, "DestroyFence"))
        return (PFN_vkVoidFunction) DestroyFence;
    if (!strcmp(name, "ResetFences"))
        return (PFN_vkVoidFunction) ResetFences;
    if (!strcmp(name, "GetFenceStatus"))
        return (PFN_vkVoidFunction) GetFenceStatus;
    if (!strcmp(name, "WaitForFences"))
        return (PFN_vkVoidFunction) WaitForFences;
    if (!strcmp(name, "CreateSemaphore"))
        return (PFN_vkVoidFunction) CreateSemaphore;
    if (!strcmp(name, "DestroySemaphore"))
        return (PFN_vkVoidFunction) DestroySemaphore;
    if (!strcmp(name, "CreateEvent"))
        return (PFN_vkVoidFunction) CreateEvent;
    if (!strcmp(name, "DestroyEvent"))
        return (PFN_vkVoidFunction) DestroyEvent;
    if (!strcmp(name, "GetEventStatus"))
        return (PFN_vkVoidFunction) GetEventStatus;
    if (!strcmp(name, "SetEvent"))
        return (PFN_vkVoidFunction) SetEvent;
    if (!strcmp(name, "ResetEvent"))
        return (PFN_vkVoidFunction) ResetEvent;
    if (!strcmp(name, "CreateQueryPool"))
        return (PFN_vkVoidFunction) CreateQueryPool;
    if (!strcmp(name, "DestroyQueryPool"))
        return (PFN_vkVoidFunction) DestroyQueryPool;
    if (!strcmp(name, "GetQueryPoolResults"))
        return (PFN_vkVoidFunction) GetQueryPoolResults;
    if (!strcmp(name, "CreateBuffer"))
        return (PFN_vkVoidFunction) CreateBuffer;
    if (!strcmp(name, "DestroyBuffer"))
        return (PFN_vkVoidFunction) DestroyBuffer;
    if (!strcmp(name, "CreateBufferView"))
        return (PFN_vkVoidFunction) CreateBufferView;
    if (!strcmp(name, "DestroyBufferView"))
        return (PFN_vkVoidFunction) DestroyBufferView;
    if (!strcmp(name, "CreateImage"))
        return (PFN_vkVoidFunction) CreateImage;
    if (!strcmp(name, "DestroyImage"))
        return (PFN_vkVoidFunction) DestroyImage;
    if (!strcmp(name, "GetImageSubresourceLayout"))
        return (PFN_vkVoidFunction) GetImageSubresourceLayout;
    if (!strcmp(name, "CreateImageView"))
        return (PFN_vkVoidFunction) CreateImageView;
    if (!strcmp(name, "DestroyImageView"))
        return (PFN_vkVoidFunction) DestroyImageView;
    if (!strcmp(name, "CreateShaderModule"))
        return (PFN_vkVoidFunction) CreateShaderModule;
    if (!strcmp(name, "DestroyShaderModule"))
        return (PFN_vkVoidFunction) DestroyShaderModule;
    if (!strcmp(name, "CreatePipelineCache"))
        return (PFN_vkVoidFunction) CreatePipelineCache;
    if (!strcmp(name, "DestroyPipelineCache"))
        return (PFN_vkVoidFunction) DestroyPipelineCache;
    if (!strcmp(name, "GetPipelineCacheData"))
        return (PFN_vkVoidFunction) GetPipelineCacheData;
    if (!strcmp(name, "MergePipelineCaches"))
        return (PFN_vkVoidFunction) MergePipelineCaches;
    if (!strcmp(name, "CreateGraphicsPipelines"))
        return (PFN_vkVoidFunction) CreateGraphicsPipelines;
    if (!strcmp(name, "CreateComputePipelines"))
        return (PFN_vkVoidFunction) CreateComputePipelines;
    if (!strcmp(name, "DestroyPipeline"))
        return (PFN_vkVoidFunction) DestroyPipeline;
    if (!strcmp(name, "CreatePipelineLayout"))
        return (PFN_vkVoidFunction) CreatePipelineLayout;
    if (!strcmp(name, "DestroyPipelineLayout"))
        return (PFN_vkVoidFunction) DestroyPipelineLayout;
    if (!strcmp(name, "CreateSampler"))
        return (PFN_vkVoidFunction) CreateSampler;
    if (!strcmp(name, "DestroySampler"))
        return (PFN_vkVoidFunction) DestroySampler;
    if (!strcmp(name, "CreateDescriptorSetLayout"))
        return (PFN_vkVoidFunction) CreateDescriptorSetLayout;
    if (!strcmp(name, "DestroyDescriptorSetLayout"))
        return (PFN_vkVoidFunction) DestroyDescriptorSetLayout;
    if (!strcmp(name, "CreateDescriptorPool"))
        return (PFN_vkVoidFunction) CreateDescriptorPool;
    if (!strcmp(name, "DestroyDescriptorPool"))
        return (PFN_vkVoidFunction) DestroyDescriptorPool;
    if (!strcmp(name, "ResetDescriptorPool"))
        return (PFN_vkVoidFunction) ResetDescriptorPool;
    if (!strcmp(name, "AllocateDescriptorSets"))
        return (PFN_vkVoidFunction) AllocateDescriptorSets;
    if (!strcmp(name, "FreeDescriptorSets"))
        return (PFN_vkVoidFunction) FreeDescriptorSets;
    if (!strcmp(name, "UpdateDescriptorSets"))
        return (PFN_vkVoidFunction) UpdateDescriptorSets;
    if (!strcmp(name, "CreateFramebuffer"))
        return (PFN_vkVoidFunction) CreateFramebuffer;
    if (!strcmp(name, "DestroyFramebuffer"))
        return (PFN_vkVoidFunction) DestroyFramebuffer;
    if (!strcmp(name, "CreateRenderPass"))
        return (PFN_vkVoidFunction) CreateRenderPass;
    if (!strcmp(name, "DestroyRenderPass"))
        return (PFN_vkVoidFunction) DestroyRenderPass;
    if (!strcmp(name, "GetRenderAreaGranularity"))
        return (PFN_vkVoidFunction) GetRenderAreaGranularity;
    if (!strcmp(name, "CreateCommandPool"))
        return (PFN_vkVoidFunction) CreateCommandPool;
    if (!strcmp(name, "DestroyCommandPool"))
        return (PFN_vkVoidFunction) DestroyCommandPool;
    if (!strcmp(name, "ResetCommandPool"))
        return (PFN_vkVoidFunction) ResetCommandPool;
    if (!strcmp(name, "AllocateCommandBuffers"))
        return (PFN_vkVoidFunction) AllocateCommandBuffers;
    if (!strcmp(name, "FreeCommandBuffers"))
        return (PFN_vkVoidFunction) FreeCommandBuffers;
    if (!strcmp(name, "BeginCommandBuffer"))
        return (PFN_vkVoidFunction) BeginCommandBuffer;
    if (!strcmp(name, "CmdBindPipeline"))
        return (PFN_vkVoidFunction) CmdBindPipeline;
    if (!strcmp(name, "CmdBindDescriptorSets"))
        return (PFN_vkVoidFunction) CmdBindDescriptorSets;
    if (!strcmp(name, "CmdBindIndexBuffer"))
        return (PFN_vkVoidFunction) CmdBindIndexBuffer;
    if (!strcmp(name, "CmdBindVertexBuffers"))
        return (PFN_vkVoidFunction) CmdBindVertexBuffers;
    if (!strcmp(name, "CmdDrawIndirect"))
        return (PFN_vkVoidFunction) CmdDrawIndirect;
    if (!strcmp(name, "CmdDrawIndexedIndirect"))
        return (PFN_vkVoidFunction) CmdDrawIndexedIndirect;
    if (!strcmp(name, "CmdDispatchIndirect"))
        return (PFN_vkVoidFunction) CmdDispatchIndirect;
    if (!strcmp(name, "CmdCopyBuffer"))
        return (PFN_vkVoidFunction) CmdCopyBuffer;
    if (!strcmp(name, "CmdCopyImage"))
        return (PFN_vkVoidFunction) CmdCopyImage;
    if (!strcmp(name, "CmdBlitImage"))
        return (PFN_vkVoidFunction) CmdBlitImage;
    if (!strcmp(name, "CmdCopyBufferToImage"))
        return (PFN_vkVoidFunction) CmdCopyBufferToImage;
    if (!strcmp(name, "CmdCopyImageToBuffer"))
        return (PFN_vkVoidFunction) CmdCopyImageToBuffer;
    if (!strcmp(name, "CmdUpdateBuffer"))
        return (PFN_vkVoidFunction) CmdUpdateBuffer;
    if (!strcmp(name, "CmdFillBuffer"))
        return (PFN_vkVoidFunction) CmdFillBuffer;
    if (!strcmp(name, "CmdClearColorImage"))
        return (PFN_vkVoidFunction) CmdClearColorImage;
    if (!strcmp(name, "CmdClearDepthStencilImage"))
        return (PFN_vkVoidFunction) CmdClearDepthStencilImage;
    if (!strcmp(name, "CmdResolveImage"))
        return (PFN_vkVoidFunction) CmdResolveImage;
    if (!strcmp(name, "CmdSetEvent"))
        return (PFN_vkVoidFunction) CmdSetEvent;
    if (!strcmp(name, "CmdResetEvent"))
        return (PFN_vkVoidFunction) CmdResetEvent;
    if (!strcmp(name, "CmdWaitEvents"))
        return (PFN_vkVoidFunction) CmdWaitEvents;
    if (!strcmp(name, "CmdPipelineBarrier"))
        return (PFN_vkVoidFunction) CmdPipelineBarrier;
    if (!strcmp(name, "CmdBeginQuery"))
        return (PFN_vkVoidFunction) CmdBeginQuery;
    if (!strcmp(name, "CmdEndQuery"))
        return (PFN_vkVoidFunction) CmdEndQuery;
    if (!strcmp(name, "CmdResetQueryPool"))
        return (PFN_vkVoidFunction) CmdResetQueryPool;
    if (!strcmp(name, "CmdWriteTimestamp"))
        return (PFN_vkVoidFunction) CmdWriteTimestamp;
    if (!strcmp(name, "CmdCopyQueryPoolResults"))
        return (PFN_vkVoidFunction) CmdCopyQueryPoolResults;
    if (!strcmp(name, "CmdPushConstants"))
        return (PFN_vkVoidFunction) CmdPushConstants;
    if (!strcmp(name, "CmdBeginRenderPass"))
        return (PFN_vkVoidFunction) CmdBeginRenderPass;

    return NULL;
}
static inline PFN_vkVoidFunction intercept_core_instance_command(const char *name)
{
    if (!name || name[0] != 'v' || name[1] != 'k')
        return NULL;

    name += 2;
    if (!strcmp(name, "CreateInstance"))
        return (PFN_vkVoidFunction) CreateInstance;
    if (!strcmp(name, "DestroyInstance"))
        return (PFN_vkVoidFunction) DestroyInstance;
    if (!strcmp(name, "GetInstanceProcAddr"))
        return (PFN_vkVoidFunction) GetInstanceProcAddr;
    if (!strcmp(name, "CreateDevice"))
        return (PFN_vkVoidFunction) CreateDevice;
    if (!strcmp(name, "EnumerateInstanceExtensionProperties"))
        return (PFN_vkVoidFunction) EnumerateInstanceExtensionProperties;
    if (!strcmp(name, "EnumerateInstanceLayerProperties"))
        return (PFN_vkVoidFunction) EnumerateInstanceLayerProperties;
    if (!strcmp(name, "EnumerateDeviceLayerProperties"))
        return (PFN_vkVoidFunction) EnumerateDeviceLayerProperties;

    return NULL;
}

// CODEGEN : file ../vk-layer-generate.py line #502
static const VkLayerProperties globalLayerProps = {
    "VK_LAYER_GOOGLE_unique_objects",
    VK_LAYER_API_VERSION, // specVersion
    1, // implementationVersion
    "Google Validation Layer"
};

VKAPI_ATTR VkResult VKAPI_CALL EnumerateInstanceLayerProperties(uint32_t *pCount,  VkLayerProperties* pProperties)
{
    return util_GetLayerProperties(1, &globalLayerProps, pCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL EnumerateDeviceLayerProperties(VkPhysicalDevice physicalDevice, uint32_t *pCount, VkLayerProperties* pProperties)
{
    return util_GetLayerProperties(1, &globalLayerProps, pCount, pProperties);
}

VKAPI_ATTR VkResult VKAPI_CALL EnumerateInstanceExtensionProperties(const char *pLayerName, uint32_t *pCount,  VkExtensionProperties* pProperties)
{
    if (pLayerName && !strcmp(pLayerName, globalLayerProps.layerName))
        return util_GetExtensionProperties(0, NULL, pCount, pProperties);

    return VK_ERROR_LAYER_NOT_PRESENT;
}

VKAPI_ATTR VkResult VKAPI_CALL EnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice,
                                                                  const char *pLayerName, uint32_t *pCount,
                                                                  VkExtensionProperties *pProperties)
{
    if (pLayerName && !strcmp(pLayerName, globalLayerProps.layerName))
        return util_GetExtensionProperties(0, nullptr, pCount, pProperties);

    assert(physicalDevice);
    VkLayerInstanceDispatchTable* pTable = get_dispatch_table(unique_objects_instance_table_map, physicalDevice);
    return pTable->EnumerateDeviceExtensionProperties(physicalDevice, NULL, pCount, pProperties);
}

// CODEGEN : file ../vk-layer-generate.py line #550
static inline PFN_vkVoidFunction intercept_wsi_enabled_command(const char *name, VkDevice dev)
{
    if (dev) {
        layer_data *my_data = get_my_data_ptr(get_dispatch_key(dev), layer_data_map);
        if (!my_data->wsi_enabled)
            return nullptr;
    }

    if (!strcmp("vkCreateSwapchainKHR", name))
        return reinterpret_cast<PFN_vkVoidFunction>(CreateSwapchainKHR);
    if (!strcmp("vkDestroySwapchainKHR", name))
        return reinterpret_cast<PFN_vkVoidFunction>(DestroySwapchainKHR);
    if (!strcmp("vkGetSwapchainImagesKHR", name))
        return reinterpret_cast<PFN_vkVoidFunction>(GetSwapchainImagesKHR);
    if (!strcmp("vkAcquireNextImageKHR", name))
        return reinterpret_cast<PFN_vkVoidFunction>(AcquireNextImageKHR);
    if (!strcmp("vkQueuePresentKHR", name))
        return reinterpret_cast<PFN_vkVoidFunction>(QueuePresentKHR);

    return nullptr;
}

VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL GetDeviceProcAddr(VkDevice device, const char* funcName)
{
    PFN_vkVoidFunction addr;
    addr = intercept_core_device_command(funcName);
    if (addr)
        return addr;
    assert(device);

    addr = intercept_wsi_enabled_command(funcName, device);
    if (addr)
        return addr;

    if (get_dispatch_table(unique_objects_device_table_map, device)->GetDeviceProcAddr == NULL)
        return NULL;
    return get_dispatch_table(unique_objects_device_table_map, device)->GetDeviceProcAddr(device, funcName);
}

// CODEGEN : file ../vk-layer-generate.py line #590
static inline PFN_vkVoidFunction intercept_wsi_enabled_command(const char *name, VkInstance instance)
{
    VkLayerInstanceDispatchTable* pTable = get_dispatch_table(unique_objects_instance_table_map, instance);
    if (instanceExtMap.size() == 0 || !instanceExtMap[pTable].wsi_enabled)
        return nullptr;

    if (!strcmp("vkDestroySurfaceKHR", name))
        return reinterpret_cast<PFN_vkVoidFunction>(DestroySurfaceKHR);
    if (!strcmp("vkGetPhysicalDeviceSurfaceSupportKHR", name))
        return reinterpret_cast<PFN_vkVoidFunction>(GetPhysicalDeviceSurfaceSupportKHR);
    if (!strcmp("vkGetPhysicalDeviceSurfaceCapabilitiesKHR", name))
        return reinterpret_cast<PFN_vkVoidFunction>(GetPhysicalDeviceSurfaceCapabilitiesKHR);
    if (!strcmp("vkGetPhysicalDeviceSurfaceFormatsKHR", name))
        return reinterpret_cast<PFN_vkVoidFunction>(GetPhysicalDeviceSurfaceFormatsKHR);
    if (!strcmp("vkGetPhysicalDeviceSurfacePresentModesKHR", name))
        return reinterpret_cast<PFN_vkVoidFunction>(GetPhysicalDeviceSurfacePresentModesKHR);

    return nullptr;
}

// CODEGEN : file ../vk-layer-generate.py line #590
static inline PFN_vkVoidFunction intercept_android_enabled_command(const char *name, VkInstance instance)
{
    VkLayerInstanceDispatchTable* pTable = get_dispatch_table(unique_objects_instance_table_map, instance);
    if (instanceExtMap.size() == 0 || !instanceExtMap[pTable].android_enabled)
        return nullptr;

#ifdef VK_USE_PLATFORM_ANDROID_KHR
    if ((instanceExtMap[pTable].android_enabled == true) && !strcmp("vkCreateAndroidSurfaceKHR", name))
        return reinterpret_cast<PFN_vkVoidFunction>(CreateAndroidSurfaceKHR);
#endif  // VK_USE_PLATFORM_ANDROID_KHR

    return nullptr;
}

VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL GetInstanceProcAddr(VkInstance instance, const char* funcName)
{
    PFN_vkVoidFunction addr;
    addr = intercept_core_instance_command(funcName);
    if (!addr) {
        addr = intercept_core_device_command(funcName);
    }
    if (!addr) {
        addr = intercept_wsi_enabled_command(funcName, VkDevice(VK_NULL_HANDLE));
    }
    if (addr) {
        return addr;
    }
    assert(instance);

    addr = intercept_wsi_enabled_command(funcName, instance);
    if (addr)
        return addr;

    addr = intercept_android_enabled_command(funcName, instance);
    if (addr)
        return addr;

    if (get_dispatch_table(unique_objects_instance_table_map, instance)->GetInstanceProcAddr == NULL) {
        return NULL;
    }
    return get_dispatch_table(unique_objects_instance_table_map, instance)->GetInstanceProcAddr(instance, funcName);
}


} // namespace unique_objects

// CODEGEN : file ../vk-layer-generate.py line #382
// loader-layer interface v0, just wrappers since there is only a layer

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateInstanceExtensionProperties(const char *pLayerName, uint32_t *pCount,  VkExtensionProperties* pProperties)
{
    return unique_objects::EnumerateInstanceExtensionProperties(pLayerName, pCount, pProperties);
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateInstanceLayerProperties(uint32_t *pCount,  VkLayerProperties* pProperties)
{
    return unique_objects::EnumerateInstanceLayerProperties(pCount, pProperties);
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateDeviceLayerProperties(VkPhysicalDevice physicalDevice, uint32_t *pCount, VkLayerProperties* pProperties)
{
    // the layer command handles VK_NULL_HANDLE just fine internally
    assert(physicalDevice == VK_NULL_HANDLE);
    return unique_objects::EnumerateDeviceLayerProperties(VK_NULL_HANDLE, pCount, pProperties);
}

VK_LAYER_EXPORT VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetDeviceProcAddr(VkDevice dev, const char *funcName)
{
    return unique_objects::GetDeviceProcAddr(dev, funcName);
}

VK_LAYER_EXPORT VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetInstanceProcAddr(VkInstance instance, const char *funcName)
{
    return unique_objects::GetInstanceProcAddr(instance, funcName);
}

VK_LAYER_EXPORT VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice,
                                                                                    const char *pLayerName, uint32_t *pCount,
                                                                                    VkExtensionProperties *pProperties)
{
    // the layer command handles VK_NULL_HANDLE just fine internally
    assert(physicalDevice == VK_NULL_HANDLE);
    return unique_objects::EnumerateDeviceExtensionProperties(VK_NULL_HANDLE, pLayerName, pCount, pProperties);
}
