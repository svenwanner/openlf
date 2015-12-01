The OpenLF circuit editor
========

[TOC]

# The OpenLF circuit editor {#editor}


\image html editor_points.png

## GUI components {#ed_comp}

1. Menu options:
  - File->New Circuit - will create a new circuit and show it in the central area, the new circuit will also be shown in the circuit list on the left and as a component on the right.
  - View->Use Tabs - switch central view between tabbed (default) and subwindow mode
2. All Circuits will be listed here, select to show selected circuit in central view
3. A list of currently shown circuits, you can close individual circuits an reopen them using (2)
4. Circuit Toolbar - from left to right: open circuit file (.gml), save current circuit to file, zoom in, zoom out, fit zoom, pop in (move subwindow into central widget), pop out (put current circuit view into extra subwindow), tick (execute current circuit)
5. Component list - all components useable within circuits are shown here, double click to insert one. Circuits can also be used as components and are therefore also listed here. Note that what is actuall inserted is a clone of the respective circuit or component.
6. Circuit Graph/Flow Chart, contains all components and connections, click and drag an input or output pad onto a corresponding pad on a second circuit to make a connection. Right click to remove components and connections.
7. Selecting an output pad will enable (9), double click on an output pad will show the current output in clifview. This is most useful after circuits have ticket to inspect the results of an operation.
8. Select a component and (10) will show the corresponding parameters
9. Component Output - after executing a circuit outputs pad still "contain" the data passed through them which can by inspected with clifview
10. for each parameter of a selected component the following elements are shown (from left to right): reset (reset to default or automatically determined value), parameter name, value (a string/filename in this case), for strings only: button to open file selection dialog, parameter alias (the circuit will show this parameter as it's own under the name entered here, alias may be the same for different parameters of same type)
11. Circuit data - the name is used for display purposes, while the type is used to identify circuits when used as components or settings. If you have a circuit (A) which contains a circuit (B) as parameter or as component and you want to save (A) to disk and load it at a later time, then (B) needs to be stored as a .gml file in OPENLF_COMPONENT_PATH which is scanned at startup.


## Example workflow {#ed_example}

The following will give a description on how to load an example structure tensor and generate a mesh using the GUI:
- Load (4) *components/st_default.gml* and give it a name (11).
- Now create a second circuit (1) and add three components (5): readCLIF, procEPI2D and WriteMesh. connect them in this order.
- Select an input file (10) for readCLIF and an output filename for writeMesh.
- Select the procEPI2D component and select the loaded structure tensor circuit as epiCircuit. Change the remaining parameters to suit (the disparity/... and merge/... parameters are forwarded from the selected circuit).
- Tick the circuit (4). Components will turn gray (which means 0% progress) and one by one fade to green again as they progress.
- After the circuit has executed (all components must have turned green again) you may inspect the results using e.g. meshlab for the mesh, or by double clicking on the procEPI2D output pad to open clifview (7).
- Optional: start modifying the structure tensor circuit and tick again to compare results - both clifview and meshlab allow viewing multiple datasets and switching between them to visually compare results.
- Optional: store the resulting circuit (4) for direct reuse at a later point or to execute it via the comman line interface of openlf.