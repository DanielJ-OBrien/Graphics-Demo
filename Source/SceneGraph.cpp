#include "SceneGraph.h"

bool SceneGraph::Initialise() {
	for (SceneNodePointer ptr : _children) {
		if (!ptr->Initialise()){
			return false;
		}
	}
	return true;
}

void SceneGraph::Update(const Matrix& worldTransformation) {
	_cumulativeWorldTransformation = _thisWorldTransformation * worldTransformation;
	for (SceneNodePointer ptr : _children) {
		ptr->Update(_cumulativeWorldTransformation);
	};
};

void SceneGraph::Render(void) {
	for (SceneNodePointer ptr : _children) {
		ptr->Render();
	}
};

void SceneGraph::Shutdown(void) {
	for (SceneNodePointer ptr : _children) {
		ptr->Shutdown();
	}
};

void SceneGraph:: Add(SceneNodePointer node) {
	_children.push_back(node);
};

void SceneGraph::Remove(SceneNodePointer node) {
	for (auto x = _children.begin(); x != _children.end(); x++) {
		SceneNodePointer ptr = *x;
		SceneNode::Remove(ptr);
		if (ptr == node) {
			_children.erase(x);
			break;
		}
	}
}

SceneNodePointer SceneGraph::Find(wstring name) {
	if (_name == name) {
		return shared_from_this(); 
	}

	for (SceneNodePointer ptr : _children) {
		SceneNodePointer node = ptr->Find(name);
		if (node) {
			return node;
		}
	}

	return nullptr;
}

