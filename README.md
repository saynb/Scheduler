# Scheduler

## Build instructions->

```
git clone https://github.com/saynb/Scheduler
```

make a build directory parallel to this repo directory, say scheduler_build

from inside the build directory give this command
```
cmake -G Xcode ../scheduler
```

Open the built xcodeproj file in xcode and build all.

Run the process 'scheduler'

There is a Client_lib present using which user programs can send TCP requests to
the scheduler to schedule jobs. This can be helpful to schedule jobs remotely

An executable called ping_test is present to schedule ping jobs and test it out.

Unit tests in progress.


