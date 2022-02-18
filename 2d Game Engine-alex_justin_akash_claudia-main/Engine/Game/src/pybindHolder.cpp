
#include "Engine.hpp"
#include "ResourceManager.hpp"
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(mygameengine, m) {
    m.doc() = "our game engine as a library"; // Optional docstring
    py::class_<Engine>(m, "Engine")
        .def(py::init<>())   // our constructor
        .def("mainGameLoop", &Engine::MainGameLoop)
	    .def("initializeGraphicsSubSystem", &Engine::InitializeGraphicsSubSystem)
	    .def("update", &Engine::Update)
	    .def("render", &Engine::Render)
	    .def("input", &Engine::Input)
	    .def("getDoQuit", &Engine::getDoQuit, py::return_value_policy::copy)
	    .def("shutdown", &Engine::Shutdown)
	    .def("start", &Engine::Start);
    // py::class_<ResourceManager, std::unique_ptr<ResourceManager, py::nodelete>>(m, "ResourceManager")
        // .def(py::init([](){ return std::unique_ptr<ResourceManager, py::nodelete>(&ResourceManager::GetInstance()*); }))//;
    py::class_<ResourceManager>(m , "ResourceManager")
	    .def(py::init<>())
        .def("getInstance", &ResourceManager::GetInstance, py::return_value_policy::reference)
        .def("changeBlock", &ResourceManager::changeBlock)
        .def("changePlaceWhat", &ResourceManager::ChangePlaceWhat)
	    .def("addGameObject", &ResourceManager::AddGameObject)
	    .def("makeFruit", &ResourceManager::MakeFruit, py::return_value_policy::reference)
	    .def("makeEnemy", &ResourceManager::MakeEnemy, py::return_value_policy::reference);
}
