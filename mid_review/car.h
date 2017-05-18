// class car
#ifndef CAR_INCLUDED
#define CAR_INCLUDED

class GasTank
{
	public:
		GasTank(double initGallons) : m_gallons(initGallons) {}
		void useGas(double gallons) { m_gallons -= gallons; }
		double getNumGallons() { return m_gallons; }
	private:
		double m_gallons;
};

class Battery
{
	public:
		Battery() : m_joules(10) {}
		void useEnergy(double joules) { m_joules -= joules; }
		double getNumJoules() { return m_joules; }
	private:
		double m_joules;
};

class Car
{
	public:
		Car() : m_GT(0) {}
		Car(double gas) : m_GT(gas) {}
		virtual ~Car() {}
		virtual double drive(double miles)
		{
			double currGas = m_GT.getNumGallons();
			if (currGas < miles / 10)
			{
				m_GT.useGas(currGas);
				return currGas * 10;
			}
			else
			{
				m_GT.useGas(miles / 10);
				return miles;
			}
		}

		double cruiseControl()
		{
			return drive(100);
		}

		double gallonsLeft()
		{
			return m_GT.getNumGallons();
		}
	private:
		GasTank m_GT;
};

class HybridCar : public Car
{
	public:
		HybridCar(int batteries) : Car(batteries * 5), num_B(batteries)
		{
			m_Bs = new Battery*[num_B];
			for (int i = 0; i < num_B; ++i)
				m_Bs[i] = new Battery;
		}
		virtual ~HybridCar()
		{
			for (int i = 0; i < num_B; ++i)
				delete m_Bs[i];
			delete m_Bs;
		}
		virtual double drive(double miles)
		{
			double miles_left = miles;
			// first use batteries
			for (int i = 0; i < num_B; ++i)
			{
				double currJ = m_Bs[i]->getNumJoules();
				if (currJ < miles_left)
				{
					miles_left -= currJ;
					m_Bs[i]->useEnergy(currJ);
				}
				else
				{
					m_Bs[i]->useEnergy(miles_left);
					return miles;
				}
			}

			return miles - miles_left + Car::drive(miles_left);
		}
	private:
		Battery** m_Bs;
		int num_B;
};

#endif  // CAR_INCLUDED
