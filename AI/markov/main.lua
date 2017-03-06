local markov = require("scripts.markov")

local begin = {["C"] = 50, ["D"] = 50}
local C = {["C"] = 5, ["C sharp"] = 5,["D"] = 5, ["D sharp"] = 5,["E"] = 5, ["E sharp"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B"] = 5, ["B sharp"] = 5}
local Csharp = {["C"] = 5, ["C sharp"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B"] = 5, ["B sharp"] = 5}
local D = {["C"] = 5, ["C sharp"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B"] = 5, ["B sharp"] = 5}
local Dsharp = {["C"] = 5, ["C sharp"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B"] = 5, ["B sharp"] = 5}
local E = {["C"] = 5, ["C sharp"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E"] = 5, ["E sharp"] = 5,["F"] = 5, ["F sharp"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B"] = 5, ["B sharp"] = 5}
local Esharp = {["C"] = 5, ["C sharp"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B"] = 5, ["B sharp"] = 5}
local F = {["C"] = 5, ["C sharp"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B"] = 5, ["B sharp"] = 5}
local Fsharp = {["C"] = 5, ["C sharp"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B"] = 5, ["B sharp"] = 5}
local G = {["C"] = 5, ["C sharp"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B"] = 5, ["B sharp"] = 5}
local Gsharp = {["C"] = 5, ["C sharp"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B"] = 5, ["B sharp"] = 5}
local A = {["C"] = 5, ["C sharp"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B"] = 5, ["B sharp"] = 5}
local Asharp = {["C"] = 5, ["C sharp"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B"] = 5, ["B sharp"] = 5}
local B = {["C"] = 5, ["C sharp"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B"] = 5, ["B sharp"] = 5}
local Bsharp = {["C"] = 5, ["C sharp"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B"] = 5, ["B sharp"] = 5}
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

local node = markov.generateNote(scale, note, 10)
markov.printNode(node)
