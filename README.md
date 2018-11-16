# wave-sim

A simple wave interference simulator.

You can configure everything from the parameters.json file

Each of the Wave Sources declared in the parameters.json file will have a phase shift of the "delta shift per iteration" times the current step with its next source.

## Parameters:
~~~~
{
    "wavelength": 25,                          ## Wavelength, in Pixels, of the waves
    "delta_shift_per_iteration": 0.1,          ## Phase shift per iteration
    "compute_quantum": 2,                      ## Simulation Node Size, the higher the faster, the lower the more beautiful
    "sources": [                               ## Wave Sources coordinates
        {"x": 500, "y": 500},
        {"x": 510, "y": 510},
        {"x": 520, "y": 520},
        {"x": 530, "y": 530},
        {"x": 540, "y": 540},
        {"x": 550, "y": 550},
        {"x": 560, "y": 560}
    ]
}


~~~~
