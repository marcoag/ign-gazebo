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
    "/test/worlds/model_photo_shoot_box.sdf";
  serverConfig.SetSdfFile(sdfFile);
  Server server(serverConfig);

  // Run server
  size_t iters50 = 50u;
  server.Run(true, iters50, false);

  // Create and populate scene
  ignition::rendering::RenderEngine *engine = rendering::engine("ogre2");

  ignition::rendering::ScenePtr scene = engine->SceneById(0);
  ignition::rendering::VisualPtr root = scene->RootVisual();

  // Get camera
  std::cout << scene->NodeCount() << std::endl;
  for (unsigned int i = 0; i < scene->NodeCount(); ++i)
  {
    auto camera = std::dynamic_pointer_cast<ignition::rendering::Camera>(
        scene->NodeByIndex(i));
    if (nullptr != camera && camera->Name() == "photo_shoot::link::camera")
    {


      auto cameraImage = camera->CreateImage();
      camera->Capture(cameraImage);
    }
  }
}
