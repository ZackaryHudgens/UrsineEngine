from UrsineEngine import math
from UrsineEngine import core

env = core.get_or_create_environment()
env.create_window("backpack model test", 800, 600)

class TranslateComponent(core.Component):
    def __init__(self):
        core.Component.__init__(self)

    def update(self):
        print("translating...")
        self.get_parent().translate(math.Vector(0.1, 0.0, -0.5))

class Backpack(core.GameObject):
    def __init__(self):
        core.GameObject.__init__(self)
        #self.add_component(TranslateComponent())

backpack = Backpack()
backpack_model = core.ModelComponent()
backpack_model.load_model("backpack.obj")
backpack.add_component(backpack_model)

translate = TranslateComponent()
backpack.add_component(translate)

mainScene = core.Scene()
mainScene.add_object(backpack)

env.load_scene(mainScene)
env.run()
