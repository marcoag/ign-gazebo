/*
 * Copyright (C) 2022 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the \"License\");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an \"AS IS\" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#include <gtest/gtest.h>

#include "ignition/gazebo/Server.hh"
#include "ignition/gazebo/test_config.hh"

#include <ignition/rendering/Camera.hh>
#include <ignition/rendering/RenderEngine.hh>
#include <ignition/rendering/RenderingIface.hh>
#include <ignition/rendering/Scene.hh>
#include <ignition/rendering/Visual.hh>

using namespace ignition;
using namespace gazebo;

// The test checks the Model Photo Shoot plugin
TEST(ModelPhotoShootTest, ModelPhotoShootLoad)
{
  // Start server
  ServerConfig serverConfig;
  const auto sdfFile = std::string(PROJECT_SOURCE_PATH) +
    "/examples/worlds/model_photo_shoot.sdf";
  serverConfig.SetSdfFile(sdfFile);
  Server server(serverConfig);

  // Run server
  size_t iters50 = 50u;
  server.Run(true, iters50, false);

  // Create and populate scene
  ignition::rendering::ScenePtr scene =
    ignition::rendering::sceneFromFirstRenderEngine();
  ignition::rendering::VisualPtr root = scene->RootVisual();

  // Create camera
  ignition::rendering::CameraPtr camera = scene->CreateCamera("camera");
  camera->SetLocalPosition(0.0, 0.0, 0.0);
  camera->SetLocalRotation(0.0, 0.0, 0.0);
  camera->SetImageWidth(960);
  camera->SetImageHeight(540);
  camera->SetImageFormat(ignition::rendering::PF_R8G8B8);
  camera->SetHFOV(1.047);
  camera->SetNearClipPlane(0.1);
  camera->SetFarClipPlane(100);
  root->AddChild(camera);

  auto cameraImage = camera->CreateImage();
  camera->Capture(cameraImage);
}
