scale = 30

velocity_iterations = 6
position_iterations = 2

gravity_y = 9.81

-- type:
-- 0: static: zero mass, zero velocity, may be manually moved
-- 1: kinematic: zero mass, non-zero velocity set by user, moved by solver
-- 2: dynamic: positive mass, non-zero velocity determined by forces, moved by solver

ground_center = { 160/scale, 160/scale }
ground_size = { 80/scale, 5/scale }
ground_angle = -math.pi / 10
ground_type = 0
ground_density = 1

circle_center = { 100/scale, 50/scale }
circle_radius = 20/scale
circle_type = 2
circle_density = 1

rect_center = { 150/scale, 10/scale }
rect_size = { 50/scale, 8/scale }
rect_angle = math.pi / 5
rect_type = 2
rect_density = 1

tri_center = { 160/scale, 100/scale }
tri_polygon = { { -10/scale, -10/scale }, { 10/scale, -10/scale }, { 3 / scale, 10/scale }, { -3 / scale, 10/scale } }
tri_type = 0
tri_density = 1
