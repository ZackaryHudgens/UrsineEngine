import core

def printStuff(a, b, c):
    print(a, b, c)

def updateComponent(component):
    component.update()

class testComponent(core.Component):
    def update(self):
        print("woah")

temp = testComponent()

core.setFunc(updateComponent)
core.callFunc([temp])
