local markov = require("scripts.markov")

local begin = {["A"] = 25, ["C"] = 25, ["E"] = 25, ["F"] = 25}
local C = {["C"] = 25, ["C sharp"] = 0,["D"] = 0, ["D sharp"] = 0,["E"] = 25, ["E sharp"] = 0, ["F"] = 25, ["F sharp"] = 0, ["G"] = 0, ["G sharp"] = 0, ["A"] = 25, ["A sharp"] = 0, ["B"] = 0, ["B sharp"] = 0}
local Csharp = {["C"] = 25, ["C sharp"] = 0, ["D"] = 0, ["D sharp"] = 0, ["E"] = 25, ["E sharp"] = 0, ["F"] = 25, ["F sharp"] = 0, ["G"] = 0, ["G sharp"] = 0, ["A"] = 25, ["A sharp"] = 0, ["B"] = 0, ["B sharp"] = 0}
local D = {["C"] = 25, ["C sharp"] = 0, ["D"] = 0, ["D sharp"] = 0, ["E"] = 25, ["E sharp"] = 0, ["F"] = 25, ["F sharp"] = 0, ["G"] = 0, ["G sharp"] = 0, ["A"] = 25, ["A sharp"] = 0, ["B"] = 0, ["B sharp"] = 0}
local Dsharp = {["C"] = 25, ["C sharp"] = 0, ["D"] = 0, ["D sharp"] = 0, ["E"] = 25, ["E sharp"] = 0, ["F"] = 25, ["F sharp"] = 0, ["G"] = 0, ["G sharp"] = 0, ["A"] = 25, ["A sharp"] = 0, ["B"] = 0, ["B sharp"] = 0}
local E = {["C"] = 25, ["C sharp"] = 0, ["D"] = 0, ["D sharp"] = 0, ["E"] = 25, ["E sharp"] = 0,["F"] = 25, ["F sharp"] = 0, ["G"] = 0, ["G sharp"] = 0, ["A"] = 25, ["A sharp"] = 0, ["B"] = 0, ["B sharp"] = 0}
local Esharp = {["C"] = 25, ["C sharp"] = 0, ["D"] = 0, ["D sharp"] = 0, ["E"] = 25, ["E sharp"] = 0, ["F"] = 25, ["F sharp"] = 0, ["G"] = 0, ["G sharp"] = 0, ["A"] = 25, ["A sharp"] = 0, ["B"] = 0, ["B sharp"] = 0}
local F = {["C"] = 25, ["C sharp"] = 0, ["D"] = 0, ["D sharp"] = 0, ["E"] = 25, ["E sharp"] = 0, ["F"] = 25, ["F sharp"] = 0, ["G"] = 0, ["G sharp"] = 0, ["A"] = 25, ["A sharp"] = 0, ["B"] = 0, ["B sharp"] = 0}
local Fsharp = {["C"] = 25, ["C sharp"] = 0, ["D"] = 0, ["D sharp"] = 0, ["E"] = 25, ["E sharp"] = 0, ["F"] = 25, ["F sharp"] = 0, ["G"] = 0, ["G sharp"] = 0, ["A"] = 25, ["A sharp"] = 0, ["B"] = 0, ["B sharp"] = 0}
local G = {["C"] = 25, ["C sharp"] = 0, ["D"] = 0, ["D sharp"] = 0, ["E"] = 25, ["E sharp"] = 0, ["F"] = 25, ["F sharp"] = 0, ["G"] = 0, ["G sharp"] = 0, ["A"] = 25, ["A sharp"] = 0, ["B"] = 0, ["B sharp"] = 0}
local Gsharp = {["C"] = 25, ["C sharp"] = 0, ["D"] = 0, ["D sharp"] = 0, ["E"] = 25, ["E sharp"] = 0, ["F"] = 25, ["F sharp"] = 0, ["G"] = 0, ["G sharp"] = 0, ["A"] = 25, ["A sharp"] = 0, ["B"] = 0, ["B sharp"] = 0}
local A = {["C"] = 25, ["C sharp"] = 0, ["D"] = 0, ["D sharp"] = 0, ["E"] = 25, ["E sharp"] = 0, ["F"] = 25, ["F sharp"] = 0, ["G"] = 0, ["G sharp"] = 0, ["A"] = 25, ["A sharp"] = 0, ["B"] = 0, ["B sharp"] = 0}
local Asharp = {["C"] = 25, ["C sharp"] = 0, ["D"] = 0, ["D sharp"] = 0, ["E"] = 25, ["E sharp"] = 0, ["F"] = 25, ["F sharp"] = 0, ["G"] = 0, ["G sharp"] = 0, ["A"] = 25, ["A sharp"] = 0, ["B"] = 0, ["B sharp"] = 0}
local B = {["C"] = 25, ["C sharp"] = 0, ["D"] = 0, ["D sharp"] = 0, ["E"] = 25, ["E sharp"] = 0, ["F"] = 25, ["F sharp"] = 0, ["G"] = 0, ["G sharp"] = 0, ["A"] = 25, ["A sharp"] = 0, ["B"] = 0, ["B sharp"] = 0}
local Bsharp = {["C"] = 25, ["C sharp"] = 0, ["D"] = 0, ["D sharp"] = 0, ["E"] = 25, ["E sharp"] = 0, ["F"] = 25, ["F sharp"] = 0, ["G"] = 0, ["G sharp"] = 0, ["A"] = 25, ["A sharp"] = 0, ["B"] = 0, ["B sharp"] = 0}
local note = {["begin"] = begin,
  ["C"] = C,
  ["C sharp"] = Csharp,
  ["D"] = D,
  ["D sharp"] = Dsharp,
  ["E"] = E,
  ["E sharp"] = Esharp,
  ["F"] = F,
  ["F sharp"] = Fsharp,
  ["G"] = G,
  ["G sharp"] = Gsharp,
  ["A"] = A,
  ["A sharp"] = Asharp,
  ["B"] = B,
  ["B sharp"] = Bsharp
}

local scale = {["begin"] = {["3"] = 100},
  ["3"] = {["3"] = 100}
}

local node = markov.generateNote(scale, note, 1)
markov.printNode(node)
