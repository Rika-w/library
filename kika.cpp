#include<iostream>
#include<complex>
#include<vector>
#include<iomanip>
#include<algorithm>
#include<cmath>
//////以上はこのライブラリで使うテンプレ

#include<cstdio>
#include<cctype>
#include<math.h>
#include<string>
#include<string.h>
#include<stack>
#include<queue>
#include<utility>
#include<set>
#include<map>
#include<stdlib.h>

using namespace std;

#define ll long long
#define ld long double
#define INF 1e9
#define MOD 1000000007
#define rep(i,n) for(i=0;i<(n);i++)
#define loop(i,a,n) for(i=a;i<(n);i++)
#define all(in) in.begin(),in.end()

typedef vector<int> vi;
typedef vector<string> vs;
typedef pair<int,int> pii;

/////テンプレここから

const double PI=acos(-1);
const double EPS=1e-9; //うまくいかなかったらゆるめる
typedef complex<double> P;
typedef vector<P> G;
#define shosu(x) fixed<<setprecision(x)
#define diff(P,i) (P[(i+1)%P.size()] - P[i])

struct L : public vector<P> {
  L(const P &a, const P &b) {
    push_back(a); push_back(b);
  }
  L(){;}
};
struct C {
  P c;double r;
  C(const P &c,double r):c(c),r(r){}
  C(){;}
};

namespace std{//演算子の定義
  bool operator < (const P& a,const P& b) {
    return real(a)!= real(b) ? real(a) < real(b) : imag(a) < imag(b);
    //return imag(a) != imag(b) ? imag(a) < imag(b) : real(a) < real(b)
  }
  bool operator == (const P& a,const P& b) {
    return a.real()==b.real() && a.imag()==b.imag();
  }
}


void printP(const P &p){
  cout << shosu(10) << p.real() << " " << p.imag() << endl;
}

void printL(const L &l) {
  	cout << shosu(10) << l[0].real() << " " << l[0].imag() << " " << l[1].real() << " " << l[1].imag() << endl;
}

void printG(const G &g) {
  for(int i = 0; i < g.size(); i++){
    cout << shosu(10) << g[i].real() << " " << g[i].imag() << endl;
  }
}



double dot(P a,P b) {
  return real(conj(a)*b);
}

double cross(P a,P b) {
  return imag(conj(a)*b);
}

P orth(const P &a, const P &b) { //点aを(点bを基準として)90度回転した点
  P p = a-b;
  P q(-p.imag(), p.real());
  return q + b;
}

int ccw(P a, P b, P c) { //3点の関係性
  b -= a; c -= a;
  if (cross(b, c) > 0)   return +1;       // counter clockwise
  if (cross(b, c) < 0)   return -1;       // clockwise
  if (dot(b, c) < 0)     return +2;       // c--a--b on line
  if (norm(b) < norm(c)) return -2;       // a--b--c on line
  return 0;                               // a--c--b on line
}

P projection(const L &l, const P &p) { //pの直線l上の射影の点
  double t=dot(p-l[0],l[0]-l[1])/norm(l[0]-l[1]);
  return l[0]+t*(l[0]-l[1]);
}

P reflection(const L &l, const P &p) { //点pの直線lに関して対称な点
  return p+2.0*(projection(l,p)-p);
}

bool isorthogonal(const L &l, const L &m) { //2直線の直交判定
  return fabs(dot(l[1]-l[0], m[1]-m[0])) < EPS;
}

bool isparallel(const L &l, const L &m) { //2直線の平行判定
  return fabs(cross(l[1]-l[0],m[1]-m[0])) < EPS;
}

bool intersectLL(const L &l, const L &m) { //2直線の交差判定
  return !isparallel(l,m);
}

bool intersectSS(const L &s, const L &t) { //2線分の交差判定(完全に交差してないとだめ)
  return ccw(s[0],s[1],t[0])*ccw(s[0],s[1],t[1]) <= 0 &&
         ccw(t[0],t[1],s[0])*ccw(t[0],t[1],s[1]) <= 0;
}

bool intersectSP(const L &s, const P &p) { //直線と点の交差判定
  return abs(s[0]-p)+abs(s[1]-p)-abs(s[1]-s[0]) < EPS; // 三角不等式
}


P crosspointSS(const L &a, const L &b) { //2線分の交点
double t1=abs(cross(a[1]-a[0],b[0]-a[0]));
double t2=abs(cross(a[1]-a[0],b[1]-a[0]));
return b[0]+(b[1]-b[0])*t1/(t1+t2);
}

P crosspointLL(const L &l, const L &m) { //2直線の交点
  double A = cross(l[1] - l[0], m[1] - m[0]);
  double B = cross(l[1] - l[0], l[1] - m[0]);
  if (abs(A) < EPS && abs(B) < EPS) return m[0]; // same line
  return m[0] + B / A * (m[1] - m[0]);
}

L crosspointCL(C c,L l){ //円と直線の交点
	P pr = projection(l,c.c);
	P e = (l[1] - l[0]) / abs(l[1] - l[0]);
	double tmp = c.r * c.r - norm(pr - c.c);
	if(abs(tmp) < EPS) tmp = 0;
	double t = sqrt(tmp);
	P a = pr + t * e;
	P b = pr - t * e;
	if(b < a) swap(a,b);
	return L(a,b);
}

L crosspointCC(C a,C b){ //2円の交点
	P tmp = b.c - a.c;
	double d = abs(tmp);
	double q = acos((a.r * a.r + d * d - b.r * b.r)/(2 * a.r * d));
	double t = arg(tmp);//atan(tmp.imag()/tmp.real());
	P p1 = a.c + polar(a.r, t + q);
	P p2 = a.c + polar(a.r, t - q);
	if(p2 < p1) swap(p1,p2);
	return L(p1, p2);
}


double distancePP(const P &p, const P &q){ //2点間の距離
  return hypot(p.real()-q.real(), p.imag()-q.imag());
}

double distanceSP(const L &s, const P &p) {//直線と点との距離
  const P r = projection(s, p);
  if (intersectSP(s, r)) return abs(r - p);
  return min(abs(s[0] - p), abs(s[1] - p));
}

double distanceSS(const L &s, const L &t) {//2線分の距離
  if (intersectSS(s, t)) return 0;
  return min(min(distanceSP(s, t[0]), distanceSP(s, t[1])),
             min(distanceSP(t, s[0]), distanceSP(t, s[1])));
}




P turn(P p,double t){ // 回転
    return p*exp(P(.0,t*PI/180.0));
}


vector<L> tangentCC(C a,C b){ //2円の接線
	if(a.r < b.r) swap(a,b);
	double d = abs(a.c - b.c);
	vector<L> l;
	if(d < EPS) return l;
	if(a.r + b.r < d - EPS){ //離れている
		double t = acos((a.r + b.r)/d);
		t = t * 180 / PI;
		l.push_back(L(a.c + turn(a.r/d*(b.c-a.c), t), b.c + turn(b.r / d * (a.c-b.c), t)));
		l.push_back(L(a.c + turn(a.r/d*(b.c-a.c), -t), b.c + turn(b.r / d * (a.c-b.c), -t)));
	}else if(a.r + b.r < d + EPS){ //外接
		P p = a.c + a.r / d * (b.c - a.c);
		l.push_back(L(p, p + turn(b.c - a.c, 90)));
	}
	if(abs(a.r - b.r) < d - EPS){ //交わっている
		double t1 = acos((a.r - b.r) / d);
		t1 = t1 * 180 / PI;
		double t2 = 180 - t1;
		l.push_back(L(a.c + turn(a.r / d * (b.c-a.c), t1), b.c + turn(b.r / d * (a.c - b.c), -t2)));
		l.push_back(L(a.c + turn(a.r / d * (b.c - a.c), -t1),b.c + turn(b.r / d * (a.c - b.c), t2)));
	}else if(abs(a.r - b.r) < d + EPS){ //内接
		P p = a.c + a.r / d * (b.c - a.c);
		l.push_back(L(p, p + turn(b.c - a.c, 90)));
	}
	return l;
}

L tangentCP(const C &c, const P &p) { //円cの外部にある点pを通るcの接線の接点
  double d = distancePP(c.c,p);
  double r = sqrt(d*d - c.r * c.r);
  C cc(p,r);
  return crosspointCC(c,cc);
}


double area(const G &g) { //多角形の面積
    double S =0;
    for(int i = 0; i < g.size(); i++){
        S +=(cross(g[i],g[(i+1)%g.size()]));
    }
    return abs(S/2.0);
}

bool isconvex(const G &g) { //凸かどうか(全ての内角の大きさが180度以下)
	int n = g.size();
  for(int i = 0; i < n; i++)
    if(ccw(g[(i+n-1)%n], g[i%n], g[(i+1)%n])==-1) return false;
	return true;
}

int inconvex(const G& g, const P& p) { //多角形と点の関係
	bool in = false;
	int n = g.size();
	for(int i = 0; i < n; i++){
		P a = g[i%n] - p;
		P b = g[(i+1)%n] - p;
		if(imag(a) > imag(b)) swap(a, b);
		if(imag(a) < EPS && 0 < imag(b))if(cross(a,b) < 0)in = !in;
		if(abs(cross(a,b)) < EPS && dot(a,b) < EPS) return 1;//ON
	}
	return in ? 2 : 0;//IN : OUT;
}

G convex_hull(G &ps) { // 凸包(点集合 P の全ての点を含む最小の凸多角形)
  int n = ps.size(), k = 0;
	sort(ps.begin(), ps.end());
	G ch(2*n);
	for(int i = 0; i < n; ch[k++] = ps[i++])//lower-hull
		while(k >= 2 && ccw(ch[k-2],ch[k-1],ps[i]) == -1) --k;//<=0  ->  ==-1
	for(int i = n-2,t = k+1; i >= 0; ch[k++] = ps[i--])//upper-hull
		while(k >= t && ccw(ch[k-2],ch[k-1],ps[i]) == -1) --k;//
	ch.resize(k-1);
	return ch;
}

double convex_diameter(const G &pt) { //凸多角形の直径(最遠頂点対間距離)
  const int n = pt.size();
  int is = 0, js = 0;
  for (int i = 1; i < n; ++i) {
    if (imag(pt[i]) > imag(pt[is])) is = i;
    if (imag(pt[i]) < imag(pt[js])) js = i;
  }
  double maxd = norm(pt[is] - pt[js]);

  int i, maxi, j, maxj;
  i = maxi = is;
  j = maxj = js;
  do {
    if (cross(diff(pt,i), diff(pt,j)) >= 0) j = (j+1) % n;
    else i = (i+1) % n;
    if (norm(pt[i] - pt[j]) > maxd) {
      maxd = norm(pt[i] - pt[j]);
      maxi = i; maxj = j;
    }
  } while (i != is || j != js);
  return sqrt(maxd); /* farthest pair is (maxi, maxj). */
}//convex_diameter(g)


G convex_cut(const G& g, const L& l) { //凸多角形の切断
  G Q;
  for (int i = 0; i < g.size(); ++i) {
    P a = g[i], b = g[(i+1)%g.size()];
    if (ccw(l[0], l[1], a) != -1) Q.push_back(a);
    if (ccw(l[0], l[1], a)*ccw(l[0], l[1], b) < 0)
      Q.push_back(crosspointLL(L(a,b), l));
  }
  return Q;
}


L PerpendicularBisector(const L &l) { //線分の垂直二等分線
  P p = l[0];
  P q((l[0].real() + l[1].real())/2.0, (l[0].imag() + l[1].imag())/2.0);
  L t(q, orth(p,q));
  return t;
}

P CircumscribedCircle(const G &g) { //三角形の外接円の半径
  L l1(g[0],g[1]);
  L l2(g[1],g[2]);
  L m1 = PerpendicularBisector(l1);
  L m2 = PerpendicularBisector(l2);
  return crosspointLL(m1, m2);
}


P inP(){
  double x,y;
//  scanf("%lf,%lf", &x, &y);
  cin >> x >> y;
  P p(x,y);
  return p;
}


L inL(){
  P p1 = inP();
  P p2 = inP();
  L l(p1,p2);
  return l;
}

C inC(){
  P p = inP();
  double r;
  cin >> r;
  C c(p,r);
  return c;
}


G inG(int n){
  G g(n);
  for(int i = 0; i < n; i++){
    g[i] = inP();
  }
  return g;
}


int main(){

}
