from UrsineEngine import core

core.initialize() # TODO: handle this automatically?

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

mainScene = core.Scene()
mainScene.add_object(player)

env = core.get_or_create_environment()
env.create_window("test", 500, 500)
env.load_scene(mainScene)
env.run()
