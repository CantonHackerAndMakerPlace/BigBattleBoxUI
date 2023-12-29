#include "idleledconfigurationwidget.h"
#include "ui_idleledconfigurationwidget.h"


IdleLedConfigurationWidget::IdleLedConfigurationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IdleLedConfigurationWidget)

{
    ui->setupUi(this);

    // Connecting buttons.
    connect(ui->saveButton, &QPushButton::clicked,
            this, &IdleLedConfigurationWidget::save);
    connect(ui->defaultButton, &QPushButton::clicked,
            this, &IdleLedConfigurationWidget::revertToDefault);
    connect(ui->cancelButton, &QPushButton::clicked,
            this, &IdleLedConfigurationWidget::cancel);


    // Connecting changes in the the drop down to the changes
    // inside of the current dropdown
    connect(ui->algorithmSelector, &AlgorithmDropDown::algorithmChanged,
            this, &IdleLedConfigurationWidget::setCurrentConfigPage);

    // Setting the current page the the selected page.
    setCurrentConfigPage(ui->algorithmSelector->getCurrentAlgorithm().value());



//    // Connecting the disabling of state based on checkbox.
//    connect(ui->linkCheckBox, &QCheckBox::stateChanged,
//            ui->p2BrightnessRangeWidget, &QWidget::setDisabled);
//    connect(ui->linkCheckBox, &QCheckBox::stateChanged,
//            ui->p2ColorSelectorWidget, &QWidget::setDisabled);
//    connect(ui->linkCheckBox, &QCheckBox::stateChanged,
//            ui->p2InterpolationWidget, &QWidget::setDisabled);



//    // connecting duration.
//    connect(&m_duration, &DefaultRestorableInt::valueChanged,
//            ui->cycleDurationSpinBox, &QSpinBox::setValue);
//    connect(ui->cycleDurationSpinBox, &QSpinBox::valueChanged,
//            &m_duration, &DefaultRestorableInt::setValue);

//    // Connecting link and checkbox.
//    connect(&m_link, &DefaultRestorableBool::valueChanged,
//            ui->linkCheckBox, &QCheckBox::setChecked);
//    connect(ui->linkCheckBox, &QCheckBox::stateChanged,
//            &m_link, &DefaultRestorableBool::setValue);

//    // Connecting player one.
//    attachColor(m_p1Color, ui->p1ColorSelectorWidget);
//    attachMaxBrightness(m_p1Maximum, ui->p1BrightnessRangeWidget);
//    attachMinBrightness(m_p1Minimum, ui->p1BrightnessRangeWidget);
//    attachCurve(m_p1Curve, ui->p1InterpolationWidget);

//    attachColor(m_p2Color, ui->p2ColorSelectorWidget);
//    attachMaxBrightness(m_p2Maximum, ui->p2BrightnessRangeWidget);
//    attachMinBrightness(m_p2Minimum, ui->p2BrightnessRangeWidget);
//    attachCurve(m_p2Curve, ui->p2InterpolationWidget);

////    connect(configuredValue, &IntegerObject::valueChanged,
////            localValue, &DefaultRestorableInt::setCurrentAndPreviousValue);
//// cycleDurationSpinBox
//// linkCheckBox

//// p1BrightnessRangeWidget
//// p1ColorSelectorWidget
//// p1InterpolationWidget

//// p2BrightnessRangeWidget
//// p2ColorSelectorWidget
//// p2InterpolationWidget
}
void IdleLedConfigurationWidget::setCurrentConfigPage(AlgoKindObject::AlgoKind kind) {
    switch(kind) {
    case AlgoKindObject::AlgoKind::Off:
        ui->configDisplayStack->setCurrentWidget(ui->offPage);
        break;
    case AlgoKindObject::AlgoKind::Blink:
        ui->configDisplayStack->setCurrentWidget(ui->blinkPage);
        break;
    case AlgoKindObject::AlgoKind::Breath:
        ui->configDisplayStack->setCurrentWidget(ui->breathPage);
        break;
    case AlgoKindObject::AlgoKind::CountDown:
        ui->configDisplayStack->setCurrentWidget(ui->countDownPage);
        break;
    case AlgoKindObject::AlgoKind::Cylon:
        ui->configDisplayStack->setCurrentWidget(ui->cylonPage);
        break;
    case AlgoKindObject::AlgoKind::RampUp:
        ui->configDisplayStack->setCurrentWidget(ui->rampUpPage);
        break;
    case AlgoKindObject::AlgoKind::Solid:
        ui->configDisplayStack->setCurrentWidget(ui->solidColorPage);
        break;
    default:
        qWarning() << "Received incorrect screen change";
    }
}


//void IdleLedConfigurationWidget::attachColor(
//    DefaultRestorableQColor& color,
//    ColorSelectionWidget *colorSelectorWidget)
//{
////    connect(&color, &DefaultRestorableQColor::valueChanged,
////            colorSelectorWidget, &ColorSelectionWidget::setColor);
////    connect(colorSelectorWidget, &ColorSelectionWidget::colorChanged,
////            &color, &DefaultRestorableQColor::setValue);
////    colorSelectorWidget->setColor(color.value());
//}

//void IdleLedConfigurationWidget::attachMinBrightness(
//    DefaultRestorableInt& minValue,
//    BrightnessSelectionWidget *brightnessSelectionWidget)
//{
////    connect(&minValue, &DefaultRestorableInt::valueChanged,
////            brightnessSelectionWidget, &BrightnessSelectionWidget::setMinValue);
////    connect(brightnessSelectionWidget, &BrightnessSelectionWidget::minValueChanged,
////            &minValue, &DefaultRestorableInt::setValue);
//}

//void IdleLedConfigurationWidget::attachMaxBrightness(
//    DefaultRestorableInt& maxValue,
//    BrightnessSelectionWidget *brightnessSelectionWidget)
//{
////    connect(&maxValue, &DefaultRestorableInt::valueChanged,
////            brightnessSelectionWidget, &BrightnessSelectionWidget::setMaxValue);
////    connect(brightnessSelectionWidget, &BrightnessSelectionWidget::maxValueChanged,
////            &maxValue, &DefaultRestorableInt::setValue);
//}

//void IdleLedConfigurationWidget::attachCurve(
//    DefaultRestorableCurve& curve,
//    InterpolationSelectorWidget *widget)
//{
////    connect(&curve, &DefaultRestorableCurve::valueChanged,
////            widget, &InterpolationSelectorWidget::setCurveSelection);
////    connect(widget, &InterpolationSelectorWidget::curveSelectionChanged,
////            &curve, &DefaultRestorableCurve::setValue);
////    widget->setCurveSelection(curve.value());
//}

IdleLedConfigurationWidget::~IdleLedConfigurationWidget() {
    delete ui;
}


void IdleLedConfigurationWidget::init(ApplicationState *state) {
    assert(m_state && "Can't initialize twice");
    m_state = state;

    auto idleConfig = m_state->ledConfig()->idleConfiguration();
    ui->algorithmSelector->init(&idleConfig->algoConfig().getAlgoKind());
    ui->breathPage->init(idleConfig->algoConfig().getBreath());

    // Connecting the ledConfig with the current application state.
//    connectAppState(m_duration, idleConfig->cycleDuration());
//    connectAppState(m_link, idleConfig->useP1ForBoth());

//    connectAppState(m_p1Color, idleConfig->p1Color());
//    connectAppState(m_p1Minimum, idleConfig->p1MinBrightness());
//    connectAppState(m_p1Maximum, idleConfig->p1MaxBrightness());
//    connectAppState(m_p1Curve, idleConfig->p1Interpolation());

//    connectAppState(m_p2Color, idleConfig->p2Color());
//    connectAppState(m_p2Minimum, idleConfig->p2MinBrightness());
//    connectAppState(m_p2Maximum, idleConfig->p2MaxBrightness());
//    connectAppState(m_p2Curve, idleConfig->p2Interpolation());

    // Updating all of the values in the UI with the new values.

//    ui->cycleDurationSpinBox.set

    // Initializing all of the widgets with their corresponding values.

//    connect(ui->cycleDurationSpinBox, &QSpinBox::valueChanged,
//            &m_state->ledConfig()->idleConfiguration()->cycleDuration(), &IntegerObject::setValue);
    // cycleDurationSpinBox
    // linkCheckBox

    // p1BrightnessRangeWidget
    // p1ColorSelectorWidget
    // p1InterpolationWidget

    // p2BrightnessRangeWidget
    // p2ColorSelectorWidget
    // p2InterpolationWidget
//    connect(ui->p1ColorSelectorWidget, &ColorSelectionWidget::colorChanged,
//            [&](QColor color) {
//                qDebug() << "Spec of color: " << color.spec();

//                m_state->arduinoClient()->p1SetColor(color);
//            }
//    );
}

bool IdleLedConfigurationWidget::hasChanges() const {
//    return m_duration.hasChange()  ||
//           m_link.hasChange()      ||
//           m_p1Color.hasChange()   ||
//           m_p1Minimum.hasChange() ||
//           m_p1Maximum.hasChange() ||
//           m_p1Curve.hasChange()   ||
//           m_p2Color.hasChange()   ||
//           m_p2Minimum.hasChange() ||
//           m_p2Maximum.hasChange() ||
//           m_p2Curve.hasChange();
    return ui->algorithmSelector->hasChanges()
           || ui->breathPage->hasChanges();
}

void IdleLedConfigurationWidget::save() {
    // Saving data into the configuration.
    ui->algorithmSelector->save();
    ui->breathPage->save();
//    auto idleConfig = m_state->ledConfig()->idleConfiguration();
//    idleConfig->cycleDuration().setValue(m_duration.value());
//    idleConfig->useP1ForBoth().setValue(m_link.value());

//    idleConfig->p1Color().setValue(m_p1Color.value());
//    idleConfig->p1MaxBrightness().setValue(m_p1Maximum.value());
//    idleConfig->p1MinBrightness().setValue(m_p1Minimum.value());
//    idleConfig->p1Interpolation().setValue(m_p1Curve.value());

//    idleConfig->p2Color().setValue(m_p2Color.value());
//    idleConfig->p2MaxBrightness().setValue(m_p2Maximum.value());
//    idleConfig->p2MinBrightness().setValue(m_p2Minimum.value());
//    idleConfig->p2Interpolation().setValue(m_p2Curve.value());
}

void IdleLedConfigurationWidget::cancel() {
    // Storeing the previous values.
    ui->algorithmSelector->restorePreviousValue();
    ui->breathPage->restorePreviousValue();

}

void IdleLedConfigurationWidget::revertToDefault() {
    // Restoring to default values.
    ui->algorithmSelector->restoreDefaultValue();
    ui->breathPage->restoreDefaultValue();
}

//void IdleLedConfigurationWidget::connectAppState(DefaultRestorableInt &localValue, IntegerObject& configuredValue) {
//    connect(&configuredValue, &IntegerObject::valueChanged,
//            &localValue, &DefaultRestorableInt::setCurrentAndPreviousValue);
//    localValue = configuredValue;
//}

//void IdleLedConfigurationWidget::connectAppState(DefaultRestorableBool &localValue, BooleanObject& configuredValue) {
//    connect(&configuredValue, &BooleanObject::valueChanged,
//            &localValue, &DefaultRestorableBool::setCurrentAndPreviousValue);
//    localValue = configuredValue;
//}

//void IdleLedConfigurationWidget::connectAppState(DefaultRestorableQColor &localValue, ColorObject& configuredValue) {
//    connect(&configuredValue, &ColorObject::valueChanged,
//            &localValue, &DefaultRestorableQColor::setCurrentAndPreviousValue);
//    localValue = configuredValue;
//}

//void IdleLedConfigurationWidget::connectAppState(DefaultRestorableCurve &localValue, InterpolationCurveObject& configuredValue) {
//    connect(&configuredValue, &InterpolationCurveObject::valueChanged,
//            &localValue, &DefaultRestorableCurve::setCurrentAndPreviousValue);
//    localValue = configuredValue;
//}
