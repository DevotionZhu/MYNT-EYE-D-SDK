// Copyright 2018 Slightech Co., Ltd. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#ifndef MYNTEYE_CAMERA_H_
#define MYNTEYE_CAMERA_H_
#pragma once

#include <cstdint>
#include <functional>
#include <limits>
#include <memory>
#include <vector>
#include <string>

#include "mynteye/device/device_info.h"
#include "mynteye/device/image.h"
#include "mynteye/device/open_params.h"
#include "mynteye/device/stream_info.h"
#include "mynteye/types.h"

MYNTEYE_BEGIN_NAMESPACE

#ifdef MYNTEYE_DEPRECATED_COMPAT
// @Deprecated
using InitParams = OpenParams;
// @Deprecated
using Info = Descriptor;
// @Deprecated
using CameraCtrlRectLogData = CameraCalibration;
#endif

class CameraPrivate;

class MYNTEYE_API Camera {
 public:
  using img_info_callback_t =
        std::function<void(const std::shared_ptr<ImgInfo>& info)>;
  using stream_callback_t = std::function<void(const StreamData& data)>;
  using motion_callback_t = std::function<void(const MotionData& data)>;

  Camera();
  ~Camera();

  /** Get all device infos */
  std::vector<DeviceInfo> GetDeviceInfos() const;
  /** Get all device infos */
  void GetDeviceInfos(std::vector<DeviceInfo>* dev_infos) const;

  /** Get all stream infos */
  void GetStreamInfos(const std::int32_t& dev_index,
      std::vector<StreamInfo>* color_infos,
      std::vector<StreamInfo>* depth_infos) const;

  /** Open camera */
  ErrorCode Open();
  /** Open camera with params */
  ErrorCode Open(const OpenParams& params);

  /** Whethor camera is opened or not */
  bool IsOpened() const;

  /** Get all device descriptors */
  std::shared_ptr<device::Descriptors> GetDescriptors() const;
  /** Get one device descriptor */
  std::string GetDescriptor(const Descriptor &desc) const;

  /** Get the intrinsics of camera */
  StreamIntrinsics GetStreamIntrinsics(const StreamMode& stream_mode) const;
  /** Get the extrinsics of camera */
  StreamExtrinsics GetStreamExtrinsics(const StreamMode& stream_mode) const;

  /** Write camera calibration bin file */
  bool WriteCameraCalibrationBinFile(const std::string& filename);

  /** Get the intrinsics of motion */
  MotionIntrinsics GetMotionIntrinsics() const;
  /** Get the extrinsics from left to motion */
  MotionExtrinsics GetMotionExtrinsics() const;

  /** Write device flash */
  bool WriteDeviceFlash(
      device::Descriptors *desc,
      device::ImuParams *imu_params,
      Version *spec_version = nullptr);

  /** Enable process mode, e.g. imu assembly, warm_drift */
  void EnableProcessMode(const ProcessMode& mode);
  /** Enable process mode, e.g. imu assembly, warm_drift */
  void EnableProcessMode(const std::int32_t& mode);

  /**
   * Enable image infos.
   *
   * If sync is false, indicates only can get infos from callback.
   * If sync is true, indicates can get infos from callback or access it from StreamData.
   */
  void EnableImageInfo(bool sync);
  /** Disable image info. */
  void DisableImageInfo();
  /** Whethor image info enabled or not */
  bool IsImageInfoEnabled() const;
  /** Whethor image info synced or not */
  bool IsImageInfoSynced() const;

  /** Enable stream data of certain image type */
  void EnableStreamData(const ImageType& type);
  /** Disable stream data of certain image type */
  void DisableStreamData(const ImageType& type);
  /** Whethor stream data of certain image type enabled or not */
  bool IsStreamDataEnabled(const ImageType& type) const;
  /** Has any stream data enabled */
  bool HasStreamDataEnabled() const;

  /** Get latest stream data */
  StreamData GetStreamData(const ImageType& type);
  /** Get cached stream datas */
  std::vector<StreamData> GetStreamDatas(const ImageType& type);

  /**
   * Enable motion datas.
   *
   * If max_size <= 0, indicates only can get datas from callback.
   * If max_size > 0, indicates can get datas from callback or using GetMotionDatas().
   *
   * Note: if max_size > 0, the motion datas will be cached until you call GetMotionDatas().
   */
  void EnableMotionDatas(
      std::size_t max_size = std::numeric_limits<std::size_t>::max());
  /** Disable motion datas. */
  void DisableMotionDatas();
  /** Whethor motion datas enabled or not */
  bool IsMotionDatasEnabled() const;

  /** Get cached motion datas. Besides, you can also get them from callback */
  std::vector<MotionData> GetMotionDatas();

  /** Set image info callback. */
  void SetImgInfoCallback(img_info_callback_t callback, bool async = true);

  /** Set stream data callback. */
  void SetStreamCallback(const ImageType& type, stream_callback_t callback,
        bool async = true);

  /** Set motion data callback. */
  void SetMotionCallback(motion_callback_t callback, bool async = true);

  /** Close the camera */
  void Close();

#ifdef MYNTEYE_DEPRECATED_COMPAT
  // @Deprecated

  /** @deprecated Replaced by GetDeviceInfos() */
  std::vector<DeviceInfo> GetDevices() const;
  /** @deprecated Replaced by GetDeviceInfos(std::vector<DeviceInfo>*) */
  void GetDevices(std::vector<DeviceInfo>* dev_infos) const;

  /** @deprecated Replaced by GetStreamInfos() */
  void GetResolutions(
      const std::int32_t& dev_index,
      std::vector<StreamInfo>* color_infos,
      std::vector<StreamInfo>* depth_infos) const;

  /** @deprecated Useless */
  // StreamMode GetStreamMode();

  /** @deprecated Useless */
  void Wait() const;

  /** @deprecated Replaced by GetDescriptor() */
  std::string GetInfo(const Info &info) const;

  /** @deprecated Replaced by GetCameraCalibration() */
  CameraCtrlRectLogData GetHDCameraCtrlData();
  /** @deprecated Replaced by GetCameraCalibration() */
  CameraCtrlRectLogData GetVGACameraCtrlData();

  /** @deprecated Replaced by GetCameraCalibrationFile()
   *              Saved to RectfyLog_PUMA_1.txt */
  void GetHDCameraLogDataFile();
  /** @deprecated Replaced by GetCameraCalibrationFile()
   *              Saved to RectfyLog_PUMA_2.txt */
  void GetVGACameraLogDataFile();

  /** @deprecated Replaced by WriteCameraCalibrationBinFile() */
  void SetCalibrationWithFile(const std::string& file_name);

  /** @deprecated Replaced by EnableProcessMode() */
  void EnableImuProcessMode(const ProcessMode &mode);

  /** @deprecated Replaced by EnableStreamData() */
  void EnableImageType(const ImageType& type);

  /** @deprecated Replaced by GetStreamData() */
  mynteye::StreamData RetrieveImage(const ImageType& type);
  /** @deprecated Replaced by GetStreamData() */
  mynteye::StreamData RetrieveImage(const ImageType& type, ErrorCode* code);

  /** @deprecated Replaced by GetStreamDatas() */
  std::vector<mynteye::StreamData> RetrieveImages(const ImageType& type);
  /** @deprecated Replaced by GetStreamDatas() */
  std::vector<mynteye::StreamData> RetrieveImages(
    const ImageType& type, ErrorCode* code);

  /** @deprecated Replaced by GetMotionDatas() */
  std::vector<MotionData> RetrieveMotions();
#endif

 private:
  std::unique_ptr<CameraPrivate> p_;
};

MYNTEYE_END_NAMESPACE

#endif  // MYNTEYE_CAMERA_H_
