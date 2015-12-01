Advanced Topics
========

[TOC]

# Advanced Topics {#adv_topics}

## Component programming {#adv_comps}

### Progress Reporting {#adv_progress}

Normally when executing components automatically report two stages of progress: 0% and 100%. For longer running tasks it is possible to add progress reporting. Simply use the `progress_(float)` method in your `Process_` method and pass current progress as a fraction between 0 and 1:
~~~~~~~~~~~~~~~~{.cpp}
progress_(0.5); // we're half way done!
~~~~~~~~~~~~~~~~
You can call this fairly often, openlf will not actually forward each call, for example the epi processor reports progress for each epi (each "line" in an input image).