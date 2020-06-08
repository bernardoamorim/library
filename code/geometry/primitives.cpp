// Geometric Primitives
// Original code: https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Primitivas/geometria.cpp

typedef double ld;
const ld DINF = 1e18;
const ld pi = acos(-1.0);
const ld eps = 1e-9;

#define sq(x) ((x)*(x))

bool eq(ld a, ld b) {
	return abs(a - b) <= eps;
}

// point
struct pt {
	ld x, y;
	pt() {}
	pt(ld x_, ld y_) : x(x_), y(y_) {}
	bool operator < (const pt p) const {
		if (!eq(x, p.x)) return x < p.x;
		if (!eq(y, p.y)) return y < p.y;
		return 0;
	}
	bool operator == (const pt p) const {
		return eq(x, p.x) and eq(y, p.y);
	}
	pt operator + (const pt p) const { return pt(x+p.x, y+p.y); }
	pt operator - (const pt p) const { return pt(x-p.x, y-p.y); }
	pt operator * (const ld c) const { return pt(x*c  , y*c  ); }
	pt operator / (const ld c) const { return pt(x/c  , y/c  ); }
	ld operator * (const pt p) const { return x*p.x + y*p.y; }
	ld operator ^ (const pt p) const { return x*p.y - y*p.x; }
	friend istream& operator >> (istream& in, pt& p) {
		return in >> p.x >> p.y;
	}
};

// line
struct line {
	pt p, q;
	line() {}
	line(pt p_, pt q_) : p(p_), q(q_) {}
	friend istream& operator >> (istream& in, line& r) {
		return in >> r.p >> r.q;
	}
};

// POINT and VECTOR

// distance
ld dist(pt p, pt q) { return hypot(p.y - q.y, p.x - q.x); }

// distance squared 
ld dist2(pt p, pt q) { return sq(p.x - q.x) + sq(p.y - q.y); }

// vector norm
ld norm(pt v) { return dist(pt(0, 0), v); }

// angle of the vector with the x-axis
ld angle(pt v) { 
	ld ang = atan2(v.y, v.x);
	if (ang < 0) ang += 2*pi;
	return ang;
}

// area with sign
//
// can be used to discover wheter a point is to the left 
// or to the right of a line
ld sarea(pt p, pt q, pt r) {
	return ((q-p)^(r-q))/2;
}

// if p, q, r are colinear
bool col(pt p, pt q, pt r) { return eq(sarea(p, q, r), 0); }

// if u and v are parallel 
// returns 1 if in same direction and -1 if in different directions
int paral(pt u, pt v) { 
	if (!eq(u^v, 0)) return 0;
	if ((u.x > eps) == (v.x > eps) and (u.y > eps) == (v.y > eps))
		return 1;
	return -1;
}

// to be discovered {se p, q, r sao ccw} ?
bool ccw(pt p, pt q, pt r) { return sarea(p, q, r) > eps; }

// rotates the point in th radian
pt rotate(pt p, ld th) {
	return pt(p.x * cos(th) - p.y * sin(th),
			p.x * sin(th) + p.y * cos(th));
}

// rotates 90 degrees
pt rotate90(pt p) { return pt(-p.y, p.x); }

// LINE

// if r is vertical
bool isvert(line r) { return eq(r.p.x, r.q.x); }

// angular coeficient of r
ld getm(line r) { 
	if (isvert(r)) return DINF;
	return (r.p.y - r.q.y) / (r.p.x - r.q.x);
}

// linear coeficient of r
ld getn(line r) {
	if (isvert(r)) return DINF;
	return r.p.y - getm(r) * r.p.x;
}

// if r and s are parallel
bool paraline(line r, line s) { return paral(r.p - r.q, s.p - s.q); }

// if p belongs to the segment of r
bool isinseg(pt p, line r) { 
	if (p == r.p or p == r.q) return 1;
	return paral(p - r.p, p - r.q) == -1;
}

// returns scallar t such that t*v belongs to the line r
ld get_t(pt v, line r) { return (r.p^r.q) / ((r.p-r.q)^v); }

// projects the point p in the line r
pt proj(pt p, line r) {
	if (r.p == r.q) return r.p;
	r.q = r.q - r.p; p = p - r.p;
	pt proj = r.q * ((p*r.q) / (r.q*r.q));
	return proj + r.p;
}

// intersection r - s
pt inter(line r, line s) {
	if (paraline(r, s)) return pt(DINF, DINF);

	if (isvert(r)) return pt(r.p.x, getm(s) * r.p.x + getn(s));
	if (isvert(s)) return pt(s.p.x, getm(r) * s.p.x + getn(r));

	ld x = (getn(s) - getn(r)) / (getm(r) - getm(s));
	return pt(x, getm(r) * x + getn(r));
}

// if the segment of r intersects the segment of s
bool interseg(line r, line s) { 
	if (isinseg(r.p, s) or isinseg(r.q, s)
		or isinseg(s.p, r) or isinseg(s.q, r)) return 1;

	return ccw(r.p, r.q, s.p) != ccw(r.p, r.q, s.q) and
			ccw(s.p, s.q, r.p) != ccw(s.p, s.q, r.q);
}

// distance from a point to a line
ld disttoline(pt p, line r) { return dist(p, proj(p, r)); }

// distance from a point to a segment
ld disttoseg(pt p, line r) { 
	if (isinseg(proj(p, r), r))
		return disttoline(p, r);
	return min(dist(p, r.p), dist(p, r.q));
}

// distance between segments
ld distseg(line a, line b) { 
	if (interseg(a, b)) return 0;

	ld ret = DINF;
	ret = min(ret, disttoseg(a.p, b));
	ret = min(ret, disttoseg(a.q, b));
	ret = min(ret, disttoseg(b.p, a));
	ret = min(ret, disttoseg(b.q, a));

	return ret;
}

// POLIGON

// poligon area
ld polarea(vector<pt> v) { 
	ld ret = 0;
	for (int i = 0; i < v.size(); i++)
		ret += sarea(pt(0, 0), v[i], v[(i + 1) % v.size()]);
	return abs(ret);
}

// is a point is inside a poligon
bool inpol(pt p, vector<pt> v) { 
	if (onpol(p, v)) return 1;
	int c = 0;
	line r = line(p, pt(DINF, pi * DINF));
	for (int i = 0; i < v.size(); i++) {
		line s = line(v[i], v[(i + 1) % v.size()]);
		if (interseg(r, s)) c++;
	}
	return c % 2;
}

// if two poligons intersect
bool interpol(vector<pt> v1, vector<pt> v2) { 
	for (int i = 0; i < v1.size(); i++) if (inpol(v1[i], v2)) return 1;
	for (int i = 0; i < v2.size(); i++) if (inpol(v2[i], v1)) return 1;
	return 0;
}

// distance between poligons
ld distpol(vector<pt> v1, vector<pt> v2) { 
	if (interpol(v1, v2)) return 0;

	ld ret = DINF;

	for (int i = 0; i < v1.size(); i++) for (int j = 0; j < v2.size(); j++)
		ret = min(ret, distseg(line(v1[i], v1[(i + 1) % v1.size()]),
					line(v2[j], v2[(j + 1) % v2.size()])));
	return ret;
}

// convex hull
// Complexity:
// Time - O(n.log(n))
vector<pt> convex_hull(vector<pt> v) { 
	vector<pt> l, u;
	sort(v.begin(), v.end());
	for (int i = 0; i < v.size(); i++) {
		while (l.size() > 1 and !ccw(l[l.size()-2], l.back(), v[i]))
			l.pop_back();
		l.pb(v[i]);
	}
	for (int i = v.size() - 1; i >= 0; i--) {
		while (u.size() > 1 and !ccw(u[u.size()-2], u.back(), v[i]))
			u.pop_back();
		u.pb(v[i]);
	}
	l.pop_back(); u.pop_back();
	for (pt i : u) l.pb(i);
	return l;
}


struct convex_pol {
	vector<pt> pol;

	convex_pol(vector<pt> v) : pol(convex_hull(v)) {}
	bool is_inside(pt p) { // if the point is inside the hull - O(log(n))
		if (pol.size() == 1) return p == pol[0];
		int l = 1, r = pol.size();
		while (l < r) {
			int m = (l+r)/2;
			if (ccw(p, pol[0], pol[m])) l = m+1;
			else r = m;
		}
		if (l == 1) return isinseg(p, line(pol[0], pol[1]));
		if (l == pol.size()) return false;
		return !ccw(p, pol[l], pol[l-1]);
	}
};

bool operator < (const line& a, const line& b) { // comparator for sweepline
	if (a.p == b.p) return ccw(a.p, a.q, b.q);
	if (!eq(a.p.x, a.q.x) and (eq(b.p.x, b.q.x) or a.p.x+eps < b.p.x))
		return ccw(a.p, a.q, b.p);
	return ccw(a.p, b.q, b.p);
}

bool simple(vector<pt> v) { // if a poligon is simple - O(n log(n))
	auto intersects = [&](pair<line, int> a, pair<line, int> b) {
		if ((a.s+1)%v.size() == b.s or (b.s+1)%v.size() == a.s) return false;
		return interseg(a.f, b.f);
	};
	vector<line> seg;
	vector<pair<pt, pair<int, int>>> w;
	for (int i = 0; i < v.size(); i++) {
		pt at = v[i], nxt = v[(i+1)%v.size()];
		// points of the segment must be ordered
		if (nxt < at) swap(at, nxt);
		seg.push_back(line(at, nxt));
		w.push_back({at, {0, i}});
		w.push_back({nxt, {1, i}});
		// weird degenerate cases
		if (isinseg(v[(i+2)%v.size()], line(at, nxt))) return 0;
		if (isinseg(v[(i+v.size()-1)%v.size()], line(at, nxt))) return 0;

	}
	sort(w.begin(), w.end());
	set<pair<line, int>> se;
	for (auto i : w) {
		line at = seg[i.s.s];
		if (i.s.f == 0) {
			auto nxt = se.lower_bound({at, i.s.s});
			if (nxt != se.end() and intersects(*nxt, {at, i.s.s})) return 0;
			if (nxt != se.begin() and intersects(*(--nxt), {at, i.s.s})) return 0;
			se.insert({at, i.s.s});
		} else {
			auto nxt = se.upper_bound({at, i.s.s}), cur = nxt, prev = --cur;
			if (nxt != se.end() and prev != se.begin()
				and intersects(*nxt, *(--prev))) return 0;
			se.erase(cur);
		}
	}
	return 1;
}

// CIRCUNFERENCE

// center of the circunference from 3 points
pt getcenter(pt a, pt b, pt c) { 
	b = (a + b) / 2;
	c = (a + c) / 2;
	return inter(line(b, b + rotate90(a - b)),
			line(c, c + rotate90(a - c)));
}

// intersection of the circunf (c, r) and the line ab
vector<pt> circ_line_inter(pt a, pt b, pt c, ld r) { 
	vector<pt> ret;
	b = b-a, a = a-c;
	ld A = b*b;
	ld B = a*b;
	ld C = a*a - r*r;
	ld D = B*B - A*C;
	if (D < -eps) return ret;
	ret.push_back(c+a+b*(-B+sqrt(D+eps))/A);
	if (D > eps) ret.push_back(c+a+b*(-B-sqrt(D))/A);
	return ret;
}

// intersection of the circunference (a, r) and (b, R)
vector<pt> circ_inter(pt a, pt b, ld r, ld R) {
	vector<pt> ret;
	ld d = dist(a, b);
	if (d > r+R or d+min(r, R) < max(r, R)) return ret;
	ld x = (d*d-R*R+r*r)/(2*d);
	ld y = sqrt(r*r-x*x);
	pt v = (b-a)/d;
	ret.push_back(a+v*x + rotate90(v)*y);
	if (y > 0) ret.push_back(a+v*x - rotate90(v)*y);
	return ret;
}

// comparator for sweep angle with segments
double ang;
struct cmp {
	bool operator () (const line& a, const line& b) const {
		line r = line(pt(0, 0), rotate(pt(1, 0), ang));
		return norm(inter(r, a)) < norm(inter(r, b));
	}
};
