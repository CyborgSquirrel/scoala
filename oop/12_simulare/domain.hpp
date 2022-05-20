#ifndef domain_hpp_INCLUDED
#define domain_hpp_INCLUDED

#include <string>

enum DeviceColor {
	RED, BLUE, BLACK, YELLOW
};

class Device {
private:
	int m_id;
	std::string m_type;
	std::string m_model;
	int m_year;
	DeviceColor m_color;
	float m_price;
public:
	Device(int id, const std::string &type, const std::string &model, int year, DeviceColor color, float price);
	
	int getId() const;
	const std::string &getType() const;
	const std::string &getModel() const;
	int getYear() const;
	DeviceColor getColor() const;
	float getPrice() const;
	
	void setType(const std::string &type);
	void setModel(const std::string &model);
	void setYear(int year);
	void setColor(DeviceColor color);
	void setPrice(float price);
	
	bool operator==(const Device &other);
};

void test_device();

#endif // domain_hpp_INCLUDED

