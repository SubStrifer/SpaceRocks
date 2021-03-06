#include "cmp_ui.h"

UiComponent::UiComponent(Entity* const p)
	: Component(p) { }

void UiComponent::update(double dt) { 
	// Update text if function is assigned
	if (textUpdate != NULL)
		_parent->getComponents<TextComponent>()[0]->setText(textUpdate());
}

