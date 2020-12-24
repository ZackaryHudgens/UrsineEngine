from UrsineEngine import core

env = core.get_or_create_environment()
env.create_window("backpack model test", 800, 600)

class TranslateComponent(core.Component):
    def __init__(self):
        core.Component.__init__(self)

    def update(self):
        self.get_parent().translate([0.0, 0.0, -0.1])

class Backpack(core.GameObject):
    def __init__(self):
        core.GameObject.__init__(self)
        #self.add_component(TranslateComponent())

backpack = Backpack()
backpack_model = core.ModelComponent()
backpack_model.load_model("backpack.obj")
backpack.add_component(backpack_model)

mainScene = core.Scene()
mainScene.add_object(backpack)

env.load_scene(mainScene)
env.run()
