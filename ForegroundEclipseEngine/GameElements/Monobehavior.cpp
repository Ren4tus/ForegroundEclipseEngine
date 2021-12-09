#include <iostream>
#include <iomanip>
#include "Monobehavior.h"
#include "Time.h"
Monobehavior::Monobehavior()
{
	
	name = "Monobehavior";
}
Monobehavior::~Monobehavior()
{
}


void Monobehavior::Start()
{
	std::cout << GetName() << " : Start()" << std::endl;
}

void Monobehavior::Update()
{
	std::cout << GetName() << " : Update()" << std::endl;
}

void Monobehavior::FixedUpdate()
{
	std::cout << GetName() << "FixedUpdate()" << std::endl;
}

void Monobehavior::Init()
{
	Start();
}


