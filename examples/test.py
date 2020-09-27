from UrsineEngine import core

env = core.get_or_create_environment()
env.create_window("test", 500, 500)

class HealthComponent(core.Component):
    def __init__(self):
        core.Component.__init__(self) # TODO: handle this automatically?
        self.health = 5
        self.connect("player_hit", self.handle_player_hit)

    def handle_player_hit(self):
        print("ow!")
        self.health -= 1

    def update(self):
        print(self.health)

    def load(self):
        print("loading health component")

class PlayerObject(core.GameObject):
    def __init__(self):
        core.GameObject.__init__(self)
        self.add_component(HealthComponent())

player = PlayerObject()
temp = core.ShaderComponent("test.vert", "test.frag"); # TODO: adding this in construction deletes the ShaderComponent?
player.add_component(temp);

mainScene = core.Scene()
mainScene.add_object(player)

env.load_scene(mainScene)
env.run()
