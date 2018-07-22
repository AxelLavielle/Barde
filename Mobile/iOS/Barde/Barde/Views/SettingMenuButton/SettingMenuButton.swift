//
//  SettingMenuButton.swift
//  Barde
//
//  Created by Arnaud Perrault on 13/10/2017.
//  Copyright © 2017 Arnaud Perrault. All rights reserved.
//

import UIKit

protocol SettingMenuButtonDelegate {
    func buttonClicked(button: SettingMenuButton, sender: UIButton)
}

@IBDesignable
class SettingMenuButton: UIView {
    
    @IBOutlet var view: UIView!
    @IBOutlet weak var titleLabel: UILabel!
    @IBOutlet weak var button: UIButton!

    var delegate : SettingMenuButtonDelegate?
    @IBAction func buttonAction(_ sender: UIButton) {
        sender.backgroundColor = UIColor.lightGray
    }

    @IBAction func buttonReleaseAction(_ sender: UIButton) {
        delegate?.buttonClicked(button: self, sender: sender)
        sender.backgroundColor = UIColor.white
    }
    
    override init(frame: CGRect) {
        super.init(frame: frame)
        setupView()
    }
    
    required init?(coder aDecoder: NSCoder) {
        super.init(coder: aDecoder)
        
        setupView()
    }
    
    func setupView() {
        let bundle = Bundle(for: type(of: self))
        UINib(nibName: "SettingMenuButton", bundle: bundle).instantiate(withOwner: self, options: nil)
        
        addSubview(view)
        view.frame = bounds
    }
    
    @IBInspectable var titleButton: String? {
        get {
            return titleLabel.text
        }
        set(titleButton) {
            titleLabel.text = titleButton
        }
    }
}
