#include "scene.h"
#include "scene_composer.h"

Scene::Scene(SceneComposer* parent)
    :EventObserver(dynamic_cast<EventObserver*>(parent)),
     composerParent(parent) {

}
