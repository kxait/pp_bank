#include "Scene.h"
#include "SceneComposer.h"

Scene::Scene(SceneComposer* parent)
    :EventObserver(dynamic_cast<EventObserver*>(parent)),
     composerParent(parent) {

}
