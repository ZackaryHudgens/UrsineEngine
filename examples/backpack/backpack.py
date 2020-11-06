from UrsineEngine import core

env = core.get_or_create_environment()
env.create_window("backpack model test", 800, 600)

class HealthComponent(core.Component):
    def __init__(self):
        core.Component.__init__(self) # TODO: handle this automatically?
        self.health = 5
        self.connect("player_hit", self.handle_player_hit)

    def handle_player_hit(self):
        print("ow!")
        self.health -= 1

    def update(self):
        pass
        #print(self.health)

    def load(self):
        pass
        #print("loading health component")

class PlayerObject(core.GameObject):
    def __init__(self):
        core.GameObject.__init__(self)
        self.add_component(HealthComponent())

player = PlayerObject()

model = core.ModelComponent()
model.load_model("backpack.obj")
model.create_and_add_shader("backpack.vert", "backpack.frag")

player.add_component(model)

mainScene = core.Scene()
mainScene.add_object(player)

env.load_scene(mainScene)
env.run()
