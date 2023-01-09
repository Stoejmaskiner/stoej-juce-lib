import xmltodict
import os
import glob
from svg.path import Path, Move, Line, Arc, CubicBezier, QuadraticBezier, Close, parse_path
import inflection

directory = os.path.join('..','assets')

class Icon:
    name = ''
    width: float = 0
    height: float = 0
    lines = []
    polylines = []
    circles = []
    paths = []

    def to_c(self, idx):
        c = f''
        c = f'{c}auto {self.name}_ico = stoej::Icon(\n'
        c = f'{c}    juce::Rectangle<float>(0.f, 0.f, {self.width}f, {self.height}f),\n'
        c = f'{c}    temp{idx}\n'
        c = f'{c});'
        return c

def parse_line(obj, line):
    obj.lines.append({
        'x1':float(line['@x1']),
        'y1':float(line['@y1']),
        'x2':float(line['@x2']),
        'y2':float(line['@y2'])
    })

def parse_polyline(obj, line):
    points = line['@points']
    points = points.split(' ')
    points = list(zip(*[iter(points)]*2))
    obj.polylines.append(points)

def parse_circle(obj, circle):
    obj.circles.append({
        'cx':float(circle['@cx']),
        'cy':float(circle['@cy']),
        'r':float(circle['@r'])
    })

def parse_name(obj, raw_name):
    base_name = os.path.basename(raw_name)
    name = base_name.replace('.svg','')
    name = inflection.underscore(name)
    obj.name = name

for i, filename in enumerate(glob.iglob(f'{directory}/*.svg')):
    print(f'// {filename}')
    obj = Icon()
    parse_name(obj, filename)
    with open(filename) as fd:
        d = xmltodict.parse(fd.read())
    #pp.pprfloat(d)
    for key in d['svg']:
        if key in ['@xmlns', '@width', '@height', '@fill', '@viewBox']:
            continue
        if key == 'rect':
            obj.width = float(d['svg'][key]['@width'])
            obj.height = float(d['svg'][key]['@height'])
            continue
        if key == 'line':
            if isinstance(d['svg'][key], list):
                for line in d['svg'][key]:
                    parse_line(obj, line)
            else: 
                parse_line(obj, d['svg'][key])
            continue
        if key == 'path':
            if isinstance(d['svg'][key], list):
                for path in d['svg'][key]:
                    obj.paths.append(parse_path(path['@d']))
            else:
                obj.paths.append(parse_path(d['svg'][key]['@d']))
            continue
        if key == 'polyline':
            if isinstance(d['svg'][key], list):
                for line in d['svg'][key]:
                    parse_polyline(obj, line)
            else:
                parse_polyline(obj, d['svg'][key])
            continue
        if key == 'circle':
            if isinstance(d['svg'][key], list):
                for circle in d['svg'][key]:
                    parse_circle(obj, circle)
            else:
                parse_circle(obj, d['svg'][key])
            continue
        raise Exception(f"parse error, unhandled element: {key}")
    
    print(obj.to_c(i))