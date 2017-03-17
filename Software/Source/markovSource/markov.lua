local json = dofile("../../Source/markovSource/dkjson.lua")

local markov = {}

local probScale = {}
local probNote = {}

local node = nil

local function initLib()
  print("lolulop")
  if (os.getenv('OS')) then
    json = dofile("../Source/markovSource/dkjson.lua")
  end
end

local function addNode(actualNode)
  if node == nil then
    node = actualNode
  else
    local tmp = node
    while tmp.next do
      tmp = tmp.next
    end
    tmp.next = actualNode
  end
  return actualNode.scale, actualNode.note
end

local function nextNode(actualScale, actualNote)
  local tmpNode = {note = nil, scale = nil, next = nil}
  local actualProbScale = probScale[actualScale]
  local actualProbNote = probNote[actualNote]
  local randomScale = math.random(100)
  local randomNote = math.random(100)
  local i = 0
  for key, value in pairs(actualProbScale) do
    i = i + value
    if (i >= randomScale and value > 0) then
      tmpNode.scale = key
      break
    end
  end
  i = 0
  for key, value in pairs(actualProbNote) do
    i = i + value
    if (i >= randomNote and value > 0) then
      tmpNode.note = key
      break
    end
  end
  return tmpNode
end

function generateNote(scale, note, nbNote, randomValue)
  scale = json.decode(scale)
  note = json.decode(note)
  math.randomseed(randomValue)
  probScale = scale;
  probNote = note;
  actualScale = "begin"
  actualNote = "begin"
  local i = 0
  while i < nbNote do
    actualScale,actualNote = addNode(nextNode(actualScale, actualNote))
    i = i + 1
  end
  return json.encode(node)
end

function markov.printNode(node)
  local tmp = node
  while tmp do
    print("Note = ", tmp.note, " Gamme = ", tmp.scale)
    tmp = tmp.next
  end
end

return markov
