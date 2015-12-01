Tools
========

[TOC]

# Tools {#tools}

## Command Line {#tools_cli}

Aside from the tools available from CLIF for work on .clif files, %OpenLF ships an %openlf executable which may be used like this to execute a single circuit:
```
openlf -c somecircuitfile.gml
```

## Gui {#tools_gui}

currently all Gui components are baked into a single executable *LF_Toolbox* which is available in the *gui/* directory. In the future these will also be avalable as separate biaries. 
Starting *LF_Toolbox* shows a selection which component to start, the *Light Field Flowchart Editor* leads to the [Circuit Editor](@ref editor) and *Light Field Camera Configurator* to the camera configuration.