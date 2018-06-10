//
//  SettingsEditAccountView.swift
//  Barde
//
//  Created by Arnaud Perrault on 17/11/2017.
//  Copyright © 2017 Arnaud Perrault. All rights reserved.
//

import UIKit
import CoreData

class SettingsEditAccountView: UIViewController, UITextFieldDelegate {

    @IBOutlet weak var tfFirstName: UITextField!
    @IBOutlet weak var tfLastName: UITextField!
    @IBOutlet weak var tfUserName: UITextField!
    @IBOutlet weak var tfBirthDate: UITextField!
    @IBOutlet weak var buttonBack: UIBarButtonItem!
    
    var profilFromLocal: Profil? // optional
    var userService: UserService?

    let datePicker = UIDatePicker()
    
    func createDatePicker() {
        datePicker.datePickerMode = .date
        datePicker.maximumDate = Date.init()

        tfBirthDate.inputView = datePicker
        datePicker.addTarget(self, action: #selector(datePickerValueChanged(_:)), for: .valueChanged)
    }
    
    @objc func datePickerValueChanged(_ sender: Any) {
       let dateFormatter = DateFormatter()
        
        dateFormatter.dateStyle = .short
        dateFormatter.timeStyle = .none
        dateFormatter.dateFormat = "MM/dd/YYYY"
        
        tfBirthDate.text = dateFormatter.string(from: datePicker.date)
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        
        userService = UserService()
        
        createDatePicker()
        
        self.navigationItem.title = "My account"
        
        tfFirstName.addTarget(self, action: #selector(textFieldDidBeginEditing(_:)), for: .editingDidBegin)
        tfLastName.addTarget(self, action: #selector(textFieldDidBeginEditing(_:)), for: .editingDidBegin)
        tfUserName.addTarget(self, action: #selector(textFieldDidBeginEditing(_:)), for: .editingDidBegin)
        tfBirthDate.addTarget(self, action: #selector(textFieldDidBeginEditing(_:)), for: .editingDidBegin)

        loadUserData()
    }
  
    @IBAction func saveButton(_ sender: Any) {
        
        saveUserData()
        
        
        ad.saveContext()
        
    }
    
    func saveUserData() {
        var profil: Profil!
        
        profil = profilFromLocal
        
        if let firstname = tfFirstName.text{
            
            if (!firstname.isEmpty)
            {
                profil.firstname = firstname
            } else {
                let refreshAlert = UIAlertController(title: "Invalid \"Firstname\" field.", message: "Field \"Firstname\" can't be empty.", preferredStyle: UIAlertControllerStyle.alert)
                
                refreshAlert.addAction(UIAlertAction(title: "OK", style: .default, handler: { (action: UIAlertAction!) in
                }))
                
                present(refreshAlert, animated: true, completion: nil)
            }
        }
        if let lastname = tfLastName.text{
            if (!lastname.isEmpty)
            {
                profil.lastname = lastname
            } else {
                let refreshAlert = UIAlertController(title: "Invalid \"Lastname\" field.", message: "Field \"Lastname\" can't be empty.", preferredStyle: UIAlertControllerStyle.alert)
                
                refreshAlert.addAction(UIAlertAction(title: "OK", style: .default, handler: { (action: UIAlertAction!) in
                }))
                
                present(refreshAlert, animated: true, completion: nil)
            }
        }
        if let userName = tfUserName.text{
            if (!userName.isEmpty)
            {
                profil.username = userName
            } else {
                let refreshAlert = UIAlertController(title: "Invalid \"Username\" field.", message: "Field \"Username\" can't be empty.", preferredStyle: UIAlertControllerStyle.alert)
                
                refreshAlert.addAction(UIAlertAction(title: "OK", style: .default, handler: { (action: UIAlertAction!) in
                }))
                
                present(refreshAlert, animated: true, completion: nil)
            }
        }
        if let birthdate = tfBirthDate.text{
            if (!birthdate.isEmpty)
            {
                profil.birthdate = birthdate
            } else {
                let refreshAlert = UIAlertController(title: "Invalid \"Birthdate\" field.", message: "Field \"Birthdate\" can't be empty.", preferredStyle: UIAlertControllerStyle.alert)
                
                refreshAlert.addAction(UIAlertAction(title: "OK", style: .default, handler: { (action: UIAlertAction!) in
                }))
                
                present(refreshAlert, animated: true, completion: nil)
            }
        }
        
    }
    
    func loadUserData(){
        if let profil = profilFromLocal{
            tfFirstName.text = profil.firstname
            tfLastName.text = profil.lastname
            tfUserName.text = profil.username
            tfBirthDate.text = profil.birthdate
        }
    }
    
    func textFieldDidBeginEditing(_ textField: UITextField) {
        self.navigationItem.setHidesBackButton(true, animated: false)
        
        navigationItem.rightBarButtonItem = UIBarButtonItem(title: "OK", style: .plain, target: self, action: #selector(validChange(_:)))
        navigationItem.leftBarButtonItem = UIBarButtonItem(title: "Cancel", style: .plain, target: self, action: #selector(dismissChange(_:)))
    }
    
    @objc func validChange(_ sender: Any) {
        self.navigationItem.setHidesBackButton(false, animated: true)
        self.navigationItem.rightBarButtonItem = nil;
        self.navigationItem.leftBarButtonItem = buttonBack;
        tfFirstName.resignFirstResponder()
        tfLastName.resignFirstResponder()
        tfUserName.resignFirstResponder()
        tfBirthDate.resignFirstResponder()
        self.view.endEditing(true)
        saveUserData()
        userService?.getUserData()
        let userData: NSManagedObject = (userService?.getLocalData())!
        userService?.updateUserData(data: userData)
    }
    
    @objc func dismissChange(_ sender: Any) {
        self.navigationItem.setHidesBackButton(false, animated: true)
        self.navigationItem.rightBarButtonItem = nil;
        self.navigationItem.leftBarButtonItem = buttonBack;
        loadUserData()
        tfFirstName.resignFirstResponder()
        tfLastName.resignFirstResponder()
        tfUserName.resignFirstResponder()
        tfBirthDate.resignFirstResponder()
    }
    @IBAction func backButtonAction(_ sender: Any) {
        navigationController?.popViewController(animated: true)
        
        dismiss(animated: true, completion: nil)
    }
}

