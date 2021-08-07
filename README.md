# Orbitals
A desktop application for simple orbital calculations and visualizations

# Building
```console
cmake .
make
```

# Running the Application
```console
./OrbitalsDesktop/OrbitalsDesktop
```

# Debugging the Application with Gammaray
```console
# Only needs to be done once per session
echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope

gammaray ./OrbitalsDesktop/OrbitalsDesktop
```
