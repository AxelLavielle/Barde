//
//  CheckButton.swift
//  Barde
//
//  Created by Arnaud Perrault on 09/04/2018.
//  Copyright © 2018 Arnaud Perrault. All rights reserved.
//

import UIKit

class CheckButton: UIButton {
    var alternateButton:Array<CheckButton>?
    
    override init(frame: CGRect){
        super.init(frame: frame)
        
        unSelectedState()
        
        self.layer.cornerRadius = 6
        self.layer.borderWidth = 0.0
        self.layer.masksToBounds = true
        self.layer.borderColor = UIColor.black.cgColor

    }
    
    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
        
        unSelectedState()
        
    }
    
    override func awakeFromNib() {
        self.layer.cornerRadius = 6
        self.layer.borderWidth = 2.0
        self.layer.masksToBounds = true
    }
    
    func unselectAlternateButtons(){
        if alternateButton != nil {
            self.isSelected = true
            
            for aButton:CheckButton in alternateButton! {
                aButton.isSelected = false
            }
        }else{
            toggleButton()
        }
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        unselectAlternateButtons()
        super.touchesBegan(touches, with: event)
    }
    
    func toggleButton(){
        self.isSelected = !isSelected
    }
    
    override var isSelected: Bool {
        didSet {
            if isSelected {
                selectedState()
            } else {
                unSelectedState()
            }
        }
    }
    
    func selectedState() {
        self.layer.cornerRadius = 6
        self.layer.borderWidth = 2.0
        self.layer.backgroundColor = Utils().uicolorFromHex(rgbValue: 0xFFFFFF).cgColor
        self.setTitleColor(Utils().uicolorFromHex(rgbValue: 0xCA5E85), for: [])
    }
    
    func unSelectedState() {
        self.layer.cornerRadius = 6
        self.layer.borderWidth = 2.0
        self.layer.backgroundColor = Utils().uicolorFromHex(rgbValue: 0xCA5E85).cgColor
        self.layer.borderColor = UIColor.white.cgColor
        self.setTitleColor(Utils().uicolorFromHex(rgbValue: 0xFFFFFF), for: [])
    }
}
