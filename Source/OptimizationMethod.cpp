#include "OptimizationMethod.h"

OptimizationMethod::OptimizationMethod() : iterMade(0)
{
}

OptimizationMethod::~OptimizationMethod()
{
}

VectorX OptimizationMethod::getBestPoint()
{
	return points.back();
}

size_t OptimizationMethod::getIterNum()
{
	return iterMade;
}

AdamGradientDescent::AdamGradientDescent(double alpha, double beta1, double beta2, double epsilon)
	: OptimizationMethod(), alpha(alpha), beta1(beta1), beta2(beta2), epsilon(epsilon)
{
}

AdamGradientDescent::~AdamGradientDescent()
{
}

RandomSearch::RandomSearch(double alpha, double p, double delta) : OptimizationMethod(), alpha(alpha), p(p), delta(delta), gen(228)
{
}

RandomSearch::~RandomSearch()
{
}

ClassicGradientDescent::ClassicGradientDescent() : OptimizationMethod(), alpha(0)
{
}

ClassicGradientDescent::~ClassicGradientDescent()
{
}

void AdamGradientDescent::optimise(const VectorX &startPoint, Area &area, const Function &f, const StopCriteria &criteria)
{
	points.push_back(startPoint);
	size_t t = 0;
	size_t dim = f.getDim();
	VectorX nextPoint(dim, 0.0);
	VectorX m(dim, 0.0);
	VectorX v(dim, 0.0);
	double m_hat, v_hat;
	TransferData data;
	data.setFunc(f);
	data.setIterNum(0);
	data.setPoints(points);
	while (!criteria.check(data))
	{
		data.setIterNum(data.getIterNum() + 1);
		nextPoint = points.back();
		VectorX grad(f.grad(points.back()));
		++t;
		for (int i = 0; i < dim; ++i)
		{
			m[i] = beta1 * m[i] + (1 - beta1) * grad[i];
			v[i] = beta2 * v[i] + (1 - beta2) * grad[i] * grad[i];
			m_hat = m[i] / (1 - pow(beta1, t));
			v_hat = v[i] / (1 - pow(beta2, t));
			nextPoint[i] -= alpha * m_hat / (sqrt(v_hat) + epsilon);
		}

		if (area.inArea(nextPoint))
		{
			points.push_back(nextPoint);
			data.setPoints(points);
		}
		else
		{
			std::vector<std::pair<double, double>> bound = area.getBounds();
			double alpha_max = INFINITY;
			VectorX point = points.back();
			for (int i = 0; i < dim; ++i)
			{
				m_hat = m[i] / (1 - pow(beta1, t));
				v_hat = v[i] / (1 - pow(beta2, t));
				double grad_component = m_hat / (sqrt(v_hat) + epsilon);
				double alpha_tmp = std::max((point[i] - bound[i].first) / grad_component, (point[i] - bound[i].second) / grad_component);
				if (alpha_tmp < alpha_max)
				{
					alpha_max = alpha_tmp;
				}
			}
			for (int i = 0; i < dim; ++i)
			{
				m_hat = m[i] / (1 - pow(beta1, t));
				v_hat = v[i] / (1 - pow(beta2, t));
				point[i] -= alpha_max * m_hat / (sqrt(v_hat) + epsilon);
			}
			points.push_back(point);
			data.setPoints(points);
			break;
		}
	}
	iterMade = data.getIterNum();
}

std::string AdamGradientDescent::getName()
{
	return "AdamGradientDescent";
}

void RandomSearch::optimise(const VectorX &startPoint, Area &area, const Function &f, const StopCriteria &criteria)
{
	points.push_back(startPoint);
	size_t dim = f.getDim();
	std::uniform_real_distribution<> _p(0, 1);
	Area areaIntersected;
	Neighborhood neighborhood(delta, points.back());
	VectorX nextPoint(dim, 0.0);
	TransferData data;
	data.setFunc(f);
	data.setIterNum(0);
	data.setPoints(points);
	while (!criteria.check(data))
	{
		data.setIterNum(data.getIterNum() + 1);
		if (_p(gen) > p)
		{
			area.genRandPoint(nextPoint, gen);
			if (f(nextPoint) < f(points.back()))
			{
				points.push_back(nextPoint);
				data.setPoints(points);
			}
		}
		else
		{
			areaIntersected = intersect(area, neighborhood);
			areaIntersected.genRandPoint(nextPoint, gen);
			if (f(nextPoint) < f(points.back()))
			{
				delta *= alpha;
				points.push_back(nextPoint);
				data.setPoints(points);
				neighborhood.change(delta, points.back());
			}
		}
	}
	iterMade = data.getIterNum();
}

std::string RandomSearch::getName()
{
	return "RandomSearch";
}

double ClassicGradientDescent::alphaOptimization(const Function &func, const VectorX &point, const double maxAlpha)
{
	double eps = 1e-15;
	double l = 0;
	double r = maxAlpha;
	double lNext, rNext;
	size_t maxIter = 100;
	VectorX grad = func.grad(point);
	auto g = [&func, &point, &grad](double alpha) -> double
	{
		return func(point - alpha * grad);
	};
	for (int i = 0; (r - l > eps) && (i < maxIter); ++i)
	{
		lNext = (2 * l + r) / 3;
		rNext = (l + 2 * r) / 3;
		if (g(lNext) < g(rNext))
			r = rNext;
		else
			l = lNext;
	}
	return (l + r) / 2;
}

double ClassicGradientDescent::getMaxAlpha(Area &area, const Function &func, const VectorX &point)
{
	std::vector<std::pair<double, double>> bound = area.getBounds();
	double alphaMax = INFINITY;
	size_t dim = point.size();
	VectorX grad = func.grad(point);
	for (int i = 0; i < dim; ++i)
	{
		double alphaTmp = std::max((point[i] - bound[i].first) / grad[i], (point[i] - bound[i].second) / grad[i]);
		if (alphaTmp < alphaMax)
			alphaMax = alphaTmp;
	}
	return alphaMax;
}

void ClassicGradientDescent::optimise(const VectorX &startPoint, Area &area, const Function &f, const StopCriteria &criteria)
{
	points.push_back(startPoint);
	size_t dim = f.getDim();
	VectorX nextPoint(dim, 0.0);
	TransferData data;
	data.setFunc(f);
	data.setIterNum(0);
	data.setPoints(points);
	while (!criteria.check(data))
	{
		data.setIterNum(data.getIterNum() + 1);
		nextPoint = points.back();
		VectorX grad(f.grad(nextPoint));
		alpha = alphaOptimization(f, nextPoint, getMaxAlpha(area, f, nextPoint));
		nextPoint -= alpha * grad;
		points.push_back(nextPoint);
		data.setPoints(points);
	}
	iterMade = data.getIterNum();
}

std::string ClassicGradientDescent::getName()
{
	return "ClassicGradientDescent";
}
