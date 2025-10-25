#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "EventAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "SteppingAction.hh"

#include <G4RunManager.hh>

void ActionInitialization::Build() const {
    auto detector = static_cast<const DetectorConstruction *>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());

    // RunAction yaşam döngüsü diğer action sınıfları tarafından paylaşıldığından burada oluşturulup kayıt ediliyor.
    auto runAction = new RunAction();
    SetUserAction(runAction);

    SetUserAction(new PrimaryGeneratorAction());

    auto eventAction = new EventAction(runAction);
    SetUserAction(eventAction);

    // SteppingAction hem dedektör geometrisine hem de olay toplamına ihtiyaç duyduğundan bağımlılıkları enjekte ediyoruz.
    SetUserAction(new SteppingAction(detector, eventAction));
}
