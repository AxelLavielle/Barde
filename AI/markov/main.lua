local markov = require("scripts.markov")

local begin = {["C flat"] = 50, ["C"] = 25, ["D"] = 25}
local Cflat = {["C flat"] = 0, ["C"] = 5, ["C sharp"] = 5, ["D flat"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E flat"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F flat"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G flat"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A flat"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B flat"] = 5, ["B"] = 5, ["B sharp"] = 5}
local C = {["C flat"] = 0, ["C"] = 5, ["C sharp"] = 5, ["D flat"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E flat"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F flat"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G flat"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A flat"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B flat"] = 5, ["B"] = 5, ["B sharp"] = 5}
local Csharp = {["C flat"] = 0, ["C"] = 5, ["C sharp"] = 5, ["D flat"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E flat"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F flat"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G flat"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A flat"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B flat"] = 5, ["B"] = 5, ["B sharp"] = 5}
local Dflat = {["C flat"] = 0, ["C"] = 5, ["C sharp"] = 5, ["D flat"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E flat"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F flat"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G flat"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A flat"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B flat"] = 5, ["B"] = 5, ["B sharp"] = 5}
local D = {["C flat"] = 0, ["C"] = 5, ["C sharp"] = 5, ["D flat"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E flat"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F flat"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G flat"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A flat"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B flat"] = 5, ["B"] = 5, ["B sharp"] = 5}
local Dsharp = {["C flat"] = 0, ["C"] = 5, ["C sharp"] = 5, ["D flat"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E flat"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F flat"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G flat"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A flat"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B flat"] = 5, ["B"] = 5, ["B sharp"] = 5}
local Eflat = {["C flat"] = 0, ["C"] = 5, ["C sharp"] = 5, ["D flat"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E flat"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F flat"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G flat"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A flat"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B flat"] = 5, ["B"] = 5, ["B sharp"] = 5}
local E = {["C flat"] = 0, ["C"] = 5, ["C sharp"] = 5, ["D flat"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E flat"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F flat"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G flat"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A flat"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B flat"] = 5, ["B"] = 5, ["B sharp"] = 5}
local Esharp = {["C flat"] = 0, ["C"] = 5, ["C sharp"] = 5, ["D flat"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E flat"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F flat"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G flat"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A flat"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B flat"] = 5, ["B"] = 5, ["B sharp"] = 5}
local Fflat = {["C flat"] = 0, ["C"] = 5, ["C sharp"] = 5, ["D flat"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E flat"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F flat"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G flat"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A flat"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B flat"] = 5, ["B"] = 5, ["B sharp"] = 5}
local F = {["C flat"] = 0, ["C"] = 5, ["C sharp"] = 5, ["D flat"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E flat"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F flat"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G flat"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A flat"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B flat"] = 5, ["B"] = 5, ["B sharp"] = 5}
local Fsharp = {["C flat"] = 0, ["C"] = 5, ["C sharp"] = 5, ["D flat"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E flat"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F flat"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G flat"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A flat"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B flat"] = 5, ["B"] = 5, ["B sharp"] = 5}
local Gflat = {["C flat"] = 0, ["C"] = 5, ["C sharp"] = 5, ["D flat"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E flat"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F flat"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G flat"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A flat"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B flat"] = 5, ["B"] = 5, ["B sharp"] = 5}
local G = {["C flat"] = 0, ["C"] = 5, ["C sharp"] = 5, ["D flat"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E flat"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F flat"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G flat"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A flat"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B flat"] = 5, ["B"] = 5, ["B sharp"] = 5}
local Gsharp = {["C flat"] = 0, ["C"] = 5, ["C sharp"] = 5, ["D flat"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E flat"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F flat"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G flat"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A flat"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B flat"] = 5, ["B"] = 5, ["B sharp"] = 5}
local Aflat = {["C flat"] = 0, ["C"] = 5, ["C sharp"] = 5, ["D flat"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E flat"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F flat"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G flat"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A flat"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B flat"] = 5, ["B"] = 5, ["B sharp"] = 5}
local A = {["C flat"] = 0, ["C"] = 5, ["C sharp"] = 5, ["D flat"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E flat"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F flat"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G flat"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A flat"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B flat"] = 5, ["B"] = 5, ["B sharp"] = 5}
local Asharp = {["C flat"] = 0, ["C"] = 5, ["C sharp"] = 5, ["D flat"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E flat"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F flat"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G flat"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A flat"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B flat"] = 5, ["B"] = 5, ["B sharp"] = 5}
local Bflat = {["C flat"] = 0, ["C"] = 5, ["C sharp"] = 5, ["D flat"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E flat"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F flat"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G flat"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A flat"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B flat"] = 5, ["B"] = 5, ["B sharp"] = 5}
local B = {["C flat"] = 0, ["C"] = 5, ["C sharp"] = 5, ["D flat"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E flat"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F flat"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G flat"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A flat"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B flat"] = 5, ["B"] = 5, ["B sharp"] = 5}
local Bsharp = {["C flat"] = 0, ["C"] = 5, ["C sharp"] = 5, ["D flat"] = 5, ["D"] = 5, ["D sharp"] = 5, ["E flat"] = 5, ["E"] = 5, ["E sharp"] = 5, ["F flat"] = 5, ["F"] = 5, ["F sharp"] = 5, ["G flat"] = 5, ["G"] = 5, ["G sharp"] = 5, ["A flat"] = 5, ["A"] = 5, ["A sharp"] = 5, ["B flat"] = 5, ["B"] = 5, ["B sharp"] = 5}
local note = {["begin"] = begin,
  ["C flat"] = Cflat,
  ["C"] = C,
  ["C sharp"] = Csharp,
  ["D flat"] = Dflat,
  ["D"] = D,
  ["D sharp"] = Dsharp,
  ["E flat"] = Eflat,
  ["E"] = E,
  ["E sharp"] = Esharp,
  ["F flat"] = Fflat,
  ["F"] = F,
  ["F sharp"] = Fsharp,
  ["G flat"] = Gflat,
  ["G"] = G,
  ["G sharp"] = Gsharp,
  ["A flat"] = Aflat,
  ["A"] = A,
  ["A sharp"] = Asharp,
  ["B flat"] = Bflat,
  ["B"] = B,
  ["B sharp"] = Bsharp
}

local scale = {["begin"] = {["A"] = 25, ["B"] = 25, ["C"] = 25, ["D"] = 25},
  ["A"] = {["A"] = 25, ["B"] = 25, ["C"] = 25, ["D"] = 25},
  ["B"] = {["A"] = 25, ["B"] = 25, ["C"] = 25, ["D"] = 25},
  ["C"] = {["A"] = 25, ["B"] = 25, ["C"] = 25, ["D"] = 25},
  ["D"] = {["A"] = 25, ["B"] = 25, ["C"] = 25, ["D"] = 25}
}

local node = markov.generateNote(scale, note, 10)
markov.printNode(node)
