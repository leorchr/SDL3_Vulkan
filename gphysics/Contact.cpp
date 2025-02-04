#include "Contact.hpp"

namespace gphysics {
	void Contact::ResolveContact(Contact& contact)
	{
		Body* a = contact.a;
		Body* b = contact.b;
		a->linearVelocity = Vec::zero;
		b->linearVelocity = Vec::zero;
	}
}