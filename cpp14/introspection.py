class A(object):
  # simply overrides the 'object.__str__' method
  def __str__(self):
    return "I'm an A!"

class B(object):
  # a custom method for my custom objects that I want to serialize
  def serialize(self):
    return "I'm a  B!"

class C(object):
  def __init__(self):
    # oops! 'serialize' is not a method
    self.serialize = 0

  def __str__(self):
    return "I'm a  C!"

def serialize(obj):
  # check if obj has an attribute called 'serialize'
  if hasattr(obj, "serialize"):
    # let's check if that 'serialize' attribute is a method
    if hasattr(obj.serialize, "__call__"):
      return obj.serialize()
  # else we call the __str__ method
  return str(obj)


if __name__ == "__main__":
  a = A()
  b = B()
  c = C()

  print(serialize(a))
  print(serialize(b))
  print(serialize(c))
