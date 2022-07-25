# Støjmaskiner // Shared Code

This is code used in all Støjmaskiner plugins, free or not, open source or not. This code remains free and open source and is a peer into how some of our plugins work.

## Submodule: `distortion.h`

Simple non-linear functions and more complex distortion constructs. Fast variants are available as well for computation on embedded devices.

### `unbounded_dist` and `fast_unbounded_dist`
Soft distortion with no maximal saturation threshold. It is based on the natural log.

### Clippers
All clippers have the same API:

Precise:
```
xxx_clip(input, threshold) -> output
```

Fast:
```
fast_xxx_clip(input, threshold) -> output
```

Full list:
- `soft_clip`: based on `tanh`, reminiscent of FET, tube or tape clipping
- `medium_clip`: slightly harder than `tanh`, reminiscent of germanium diode clipping
- `firm_clip`: analog-style hard clipping, reminiscent of silicon diode clipping
- `hard_clip`: digital hard clipping
- `safe_clip`: digital hard clipping with inter-sample peak clipping
- `sin_clip`: soft clipping based on `sin`, has the property of reaching maximal saturation with finite gain
