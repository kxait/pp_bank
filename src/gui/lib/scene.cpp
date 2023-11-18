#include "scene.h"
#include "scene_composer.h"

scene::scene(scene_composer* parent)
    :event_observer(dynamic_cast<event_observer*>(parent)),
     m_composer_parent(parent) {

}
