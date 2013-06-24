#ifndef NORI_SCENE_FWD_H_
#define NORI_SCENE_FWD_H_

#include <memory>


namespace nori {

class scene;
typedef std::shared_ptr<scene> scene_ptr;

class sprite_node;
typedef std::shared_ptr<sprite_node> sprite_node_ptr;

} // namespace nori

#endif // NORI_SCENE_FWD_H_
