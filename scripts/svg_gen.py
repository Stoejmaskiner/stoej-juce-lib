import xmltodict
import os
import glob
#from svg.path import Path, Move, Line, Arc, CubicBezier, QuadraticBezier, Close, parse_path
import inflection
import numpy as np
from dataclasses import dataclass
from typing import Tuple, List

# apologies for the unreadableness, I felt like golfing

f32 = np.float32

@dataclass
class Shape:
    stroke: bool
    fill: bool
    bounds: bool

@dataclass
class Line(Shape):
    x1: float
    y1: float
    x2: float
    y2: float

@dataclass
class Rect(Shape):
    x: float
    y: float
    w: float
    h: float

@dataclass
class Circle(Shape):
    x: float
    y: float
    w: float

@dataclass
class Point:
    x: float
    y: float

class Close:
    pass

@dataclass
class CenteredArc:
    cx: float
    cy: float
    rx: float
    ry: float
    rot: float
    th1: float
    th2: float

@dataclass
class CubicTo:
    c1x: float
    c1y: float
    c2x: float
    c2y: float
    ex: float
    ey: float

class PolyLine:
    stroke: bool
    fill: bool
    bounds: bool
    start: Point
    line_tos: List[Point]

class Path:
    stroke: bool
    fill: bool
    bounds: bool
    start: Point
    shape_tos: List[Point | CenteredArc | CubicTo]



directory = os.path.join('..','assets')

# class Icon:
#     def __init__(self):
#         self.name = ''
#         self.width = 0.0
#         self.height = 0.0
#         self.lines = []
#         self.polylines = []
#         self.circles = []
#         self.arcs = []
#         self.cubics = []

#     def to_c(self):
#         c = ''
#         # c = f'{c}auto {self.name}_ico = stoej::Icon(\n'
#         # c = f'{c}    juce::Rectangle<float>(0.f, 0.f, {self.width}f, {self.height}f),\n'
#         # c = f'{c}    []() -> juce::Path {{\n'
#         # c = f'{c}        juce::Path p;\n'
#         # for line in self.lines:
#         #     c = f'{c}        p.startNewSubPath({np.float32(line["x1"])}f, {np.float32(line["y1"])}f);\n'
#         #     c = f'{c}        p.lineTo({np.float32(line["x2"])}f, {np.float32(line["y2"])}f);\n'
#         # for polyline in self.polylines:
#         #     start = polyline[0]
#         #     c = f'{c}        p.startNewSubPath({np.float32(start[0])}f, {np.float32(start[1])}f);\n'
#         #     for point in polyline[1:]:
#         #         c = f'{c}        p.lineTo({np.float32(point[0])}f, {np.float32(point[1])}f);\n'
#         # for circle in self.circles:
#         #     c = f'{c}        p.addEllipse({np.float32(circle["cx"])}f, {np.float32(circle["cy"])}f, {np.float32(circle["r"])}f, {np.float32(circle["r"])}f);\n'
#         # for arc in self.arcs:
#         #     c = f"{c}        p.addCentredArc({np.float32(arc['cx'])}f, {np.float32(arc['cy'])}f, {np.float32(arc['rx'])}f, {np.float32(arc['ry'])}f, {np.float32(arc['rot'])}f, {np.float32(arc['th1'])}f, {np.float32(arc['th2'])}f);\n"
#         # for cubic in self.cubics:
#         #     c = f"{c}        p.startNewSubPath({np.float32(cubic['x1'])}f, {np.float32(cubic['y1'])}f);\n"
#         #     c = f"{c}        p.cubicTo({np.float32(cubic['c1x'])}f, {np.float32(cubic['c1y'])}f, {np.float32(cubic['c2x'])}f, {np.float32(cubic['c2y'])}f, {np.float32(cubic['x2'])}f, {np.float32(cubic['y2'])}f);\n"
#         c = f'{c}        return p;\n'
#         c = f'{c}    }}()\n'
#         c = f'{c});\n'
#         return c

def parse_line(line) -> str:
    l = f'        p.startNewSubPath({f32(line["@x1"])}f, {f32(line["@y1"])}f);\n'
    l = f'{l}        p.lineTo({f32(line["@x2"])}f, {f32(line["@y2"])}f);\n'
    return l


def parse_polyline(line):
    points = line['@points']
    points = points.split(' ')
    points = [f32(p) for p in points]
    points = list(zip(*[iter(points)]*2))
    start = points[0]
    l = f'        p.startNewSubPath({start[0]}f, {start[1]}f);\n'
    for point in points[1:]:
        l = f'{l}        p.lineTo({point[0]}f, {point[1]}f);\n'
    return l


def parse_circle(circle):
    rx = ry = f32(circle['@r'])
    cx = f32(circle['@cx']) - rx
    cy = f32(circle['@cy']) - ry
    dx = rx * 2.0
    dy = ry * 2.0
    return f'        p.addEllipse({cx}f, {cy}f, {dx}f, {dy}f);\n'


def parse_svg_coords(coords) -> tuple:
    return (complex(coords).real, complex(coords).imag)

def my_parse_path(path) -> str:
    p = ''
    things = parse_path(path['@d'])
    for thing in things:
        match thing:
            case Move():
                continue
            case Line() | Close() as var:
                start = parse_svg_coords(var.start)
                end = parse_svg_coords(var.end)
                p = f'{p}{parse_line({"@x1": start[0],"@y1": start[1],"@x2": end[0],"@y2": end[1]})}'
            case Arc() as var:
                # ref: https://www.w3.org/TR/SVG/implnote.html#ArcImplementationNotes
                start = parse_svg_coords(var.start)
                radius = parse_svg_coords(var.radius)
                end = parse_svg_coords(var.end)
                c = np.cos(0) #var.rotation)
                s = np.sin(0) #var.rotation)
                A = np.array([[ c,  s],
                              [-s,  c]])
                v = np.array([[(start[0] - end[0]) * 0.5],
                              [(start[1] - end[1]) * 0.5]])
                v_prime = np.matmul(A, v)
                x1p = v_prime[0,0]
                y1p = v_prime[1,0]
                x1p2 = x1p**2
                y1p2 = y1p**2
                rx2 = radius[0]**2
                ry2 = radius[1]**2
                coeff = np.sqrt((rx2 * ry2 - rx2 * y1p2 - ry2 * x1p2)/(rx2 * y1p2 + ry2 * x1p2))
                if var.sweep == var.arc:
                    coeff = -coeff
                cxp = coeff * (radius[0] * y1p / radius[1])
                cyp = -coeff * (radius[1] * x1p / radius[0])
                Ap = np.array([[c, -s],
                               [s,  c]])
                cp = np.array([[cxp],[cyp]])
                b = np.array([[(start[0] + end[0]) * 0.5],
                              [(start[1] + end[1]) * 0.5]])
                c = np.matmul(Ap, cp) + b
                
                def angle(u, v):
                    sign = np.sign(u[0] * v[1] - u[1] * v[0])
                    return sign * np.arccos(np.dot(u, v) / (np.linalg.norm(u) * np.linalg.norm(v)))
                gneurshk = np.array([
                    (x1p - cxp) / radius[0],
                    (y1p - cyp) / radius[1]])
                theta_1 = np.fmod(angle(np.array([1.0,0.0]), gneurshk), 360.0)
                delta_theta = angle(gneurshk, np.array([
                    (-x1p - cxp) / radius[0],
                    (-y1p - cyp) / radius[1]]))
                theta_2 = np.fmod(theta_1 + delta_theta, 360.0)



                p = f"{p}        p.addCentredArc({f32(cxp)}f, {f32(cyp)}f, {f32(radius[0])}f, {f32(radius[1])}f, {f32(var.rotation)}f, {f32(theta_1)}f, {f32(theta_2)}f, true);\n"
            case CubicBezier() as var:
                start = parse_svg_coords(var.start)
                end = parse_svg_coords(var.end)
                control1 = parse_svg_coords(var.control1)
                control2 = parse_svg_coords(var.control2)
                p = f"{p}        p.startNewSubPath({f32(start[0])}f, {f32(start[1])}f);\n"
                p = f"{p}        p.cubicTo({f32(control1[0])}f, {f32(control1[1])}f, {f32(control2[0])}f, {f32(control2[1])}f, {f32(end[0])}f, {f32(end[1])}f);\n"
            case _:
                raise Exception(f'unhandled path element "{thing}"')
    return p


def parse_name(raw_name) -> str:
    base_name = os.path.basename(raw_name)
    name = base_name.replace('.svg','')
    return inflection.underscore(name)

def parse_shapes(d: dict) -> Tuple[str, str]:
    r = ''
    shp = '    []() -> juce::Path {\n'
    shp = f'{shp}        juce::Path p;\n'
    for key in d['svg']:
        val = d['svg'][key]
        is_list = isinstance(val, list)
        match key:
            case '@xmlns' | '@width' | '@height' | '@fill' | '@viewBox':
                continue
            case 'rect':
                w = f32(val['@width'])
                h = f32(val['@height'])
                r = f'    []() -> juce::Path {{ juce::Path p; p.addRectangle(juce::Rectangle<float>(0.f, 0.f, {w}f, {h}f)); return p; }}(),\n'
                continue
            case 'line':
                if is_list:
                    for line in val:
                        l = parse_line(line)
                        shp = f'{shp}{l}'
                    continue
                l = parse_line(val)
                shp = f'{shp}{l}'
                continue
            case 'path':
                if is_list:
                    for path in val:
                        p = my_parse_path(path)
                        shp = f'{shp}{p}'
                    continue
                p = my_parse_path(val)
                shp = f'{shp}{p}'
                continue
            case 'polyline':
                if is_list:
                    for line in val:
                        pol = parse_polyline(line)
                        shp = f'{shp}{pol}'
                    continue
                pol = parse_polyline(val)
                shp = f'{shp}{pol}'
                continue
            case 'circle':
                if is_list:
                    for circle in val:
                        c = parse_circle(circle)
                        shp = f'{shp}{c}'
                    continue
                c = parse_circle(val)
                shp = f'{shp}{c}'
                continue
        raise Exception(f"parse error, unhandled element: {key}")
    shp = f'{shp}        return p;\n'
    shp = f'{shp}    }}()\n'
    return r, shp

def svg_to_cpp(file: str) -> Tuple[str, str]:
    hpp = f'// {file}\n'
    cpp = f'// {file}\n'
    name = parse_name(file)
    hpp = f'{hpp}extern stoej::Icon {name}_ico;\n\n'
    cpp = f'{cpp}stoej::Icon {name}_ico = stoej::Icon(\n'
    with open(file) as fd:
        d = xmltodict.parse(fd.read())
    r, shp = parse_shapes(d)
    cpp = f'{cpp}{r}'
    cpp = f'{cpp}{shp}'
    cpp = f'{cpp});\n\n'
    return hpp, cpp

if __name__ == '__main__':
    hpp = '// WARNING!!! auto-generated file, do not edit!\n'
    hpp = f'{hpp}// =============================================================================\n\n'
    hpp = f'{hpp}#pragma once\n'
    hpp = f'{hpp}#include <JuceHeader.h>\n'
    hpp = f'{hpp}#include "binary_data/stoej_Icon.h"\n\n'
    hpp = f'{hpp}namespace stoej {{\n\n'

    cpp = '// WARNING!!! auto-generated file, do not edit!\n'
    cpp = f'{cpp}// =============================================================================\n\n'
    cpp = f'{cpp}#include "stoej_Svgs.h"\n\n'
    cpp = f'{cpp}namespace stoej {{\n\n'
    for file in glob.iglob(f'{directory}/*.svg'):
        hpp_, cpp_ = svg_to_cpp(file) 
        hpp = f'{hpp}{hpp_}'
        cpp = f'{cpp}{cpp_}'
    hpp = f'{hpp}}}'
    cpp = f'{cpp}}}'
    with open('../binary_data/stoej_Svgs.h', 'w') as file:
        file.write(hpp)
    with open('../binary_data/stoej_Svgs.cpp', 'w') as file:
        file.write(cpp)
    
# if __name__ == '__main__':
#     cpp = '// WARNING!!! auto-generated file, do not edit!\n'
#     cpp = f'{cpp}// =============================================================================\n\n'
#     cpp = f'{cpp}#pragma once\n'
#     cpp = f'{cpp}#include <JuceHeader.h>\n'
#     cpp = f'{cpp}#include "binary_data/stoej_Icon.h"\n\n'
#     cpp = f'{cpp}namespace stoej {{\n\n'
#     for file in glob.iglob(f'{directory}/*.svg'):
#         _, cpp_ = svg_to_cpp(file) 
#         cpp = f'{cpp}{cpp_}'
#     cpp = f'{cpp}}}'
#     with open('../binary_data/stoej_Svgs.h', 'w') as file:
#         file.write(cpp)
