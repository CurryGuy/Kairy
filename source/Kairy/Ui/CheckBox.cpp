#include <Kairy/Ui/CheckBox.h>

NS_KAIRY_BEGIN

//=============================================================================

std::shared_ptr<CheckBox> CheckBox::create(void)
{
	return std::make_shared<CheckBox>();
}

//=============================================================================

std::shared_ptr<CheckBox> CheckBox::create(const std::string & uncheckedImage, const std::string & checkedImage, const std::string & disabledImage)
{
	auto cb = std::make_shared<CheckBox>();

	if (!cb || !cb->setImages(uncheckedImage, checkedImage, disabledImage))
	{
		return nullptr;
	}

	return cb;
}

//=============================================================================

CheckBox::CheckBox()
	: Control()
	, _checkCallback(nullptr)
	, _checked(false)
{
	_uncheckedImage = std::make_shared<Sprite>();
	_checkedImage = std::make_shared<Sprite>();
	_disabledImage = std::make_shared<Sprite>();

	_uncheckedImage->setName("unchecked");
	_checkedImage->setName("checked");
	_disabledImage->setName("disabled");

	_uncheckedImage->setVisible(true);
	_checkedImage->setVisible(false);
	_disabledImage->setVisible(false);

	addChild(_uncheckedImage);
	addChild(_checkedImage);
	addChild(_disabledImage);
}

//=============================================================================

CheckBox::CheckBox(
	const std::string & uncheckedImage,
	const std::string & checkedImage,
	const std::string & disabledImage)
	: CheckBox()
{
	setImages(uncheckedImage, checkedImage, disabledImage);
}

//=============================================================================

bool CheckBox::setImages(
	const std::string & uncheckedImage,
	const std::string & checkedImage,
	const std::string & disabledImage)
{
	if (!_uncheckedImage->loadTexture(uncheckedImage))
	{
		return false;
	}

	if (!_checkedImage->loadTexture(checkedImage))
	{
		return false;
	}

	if (!_disabledImage->loadTexture(disabledImage.empty() ?
		uncheckedImage : disabledImage))
	{
		return false;
	}

	float width = std::max({
		_uncheckedImage->getSize().x,
		_checkedImage->getSize().x,
		_disabledImage->getSize().x
	});

	float height = std::max({
		_uncheckedImage->getSize().y,
		_checkedImage->getSize().y,
		_disabledImage->getSize().y
	});

	setSize(Vec2(width, height));

	return true;
}

//=============================================================================

void CheckBox::onTouchDown(const Vec2 & position, float dt)
{
	Control::onTouchDown(position, dt);

	if (_touched)
	{
		setChecked(!isChecked());

		if (_checkCallback)
			_checkCallback(isChecked());
	}
}

//=============================================================================

void CheckBox::setEnabled(bool enabled)
{
	Control::setEnabled(enabled);

	_disabledImage->setVisible(!enabled);
}

//=============================================================================

void CheckBox::setChecked(bool checked)
{
	_checked = checked;

	_uncheckedImage->setVisible(!checked);
	_checkedImage->setVisible(checked);
}

//=============================================================================

void CheckBox::setCheckCallback(const CheckCallback & callback)
{
	_checkCallback = callback;
}

//=============================================================================

void CheckBox::setColor(const Color & color)
{
	Node::setColor(color);

	_uncheckedImage->setColor(color);
	_checkedImage->setColor(color);
	_disabledImage->setColor(color);
}

//=============================================================================

NS_KAIRY_END
