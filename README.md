# Two-Factor Authentication Nudge

### Overview

A strict policy of requiring two-factor authentication can sometimes be onerous for users. The purpose of this module is to help site administrators give users a gentle, but insistent [nudge] (https://en.wikipedia.org/wiki/Nudge_(book)) to set up two-factor authentication.

It makes two fields available to the [Administration Views] (https://www.drupal.org/project/admin_views) module: <i>Two-factor Security Status</i> and <i>Two-factor Saved Date</i>. It also provides a filter that can be exposed to selectively display a list of users based on their TFA status.

### Requirements

* [Two-factor Authentication (TFA)] (https://www.drupal.org/project/tfa)
* [TFA Basic plugins] (https://www.drupal.org/project/tfa_basic)
* [Administration Views] (https://www.drupal.org/project/admin_views)

### Installation

 1. download and enable tfa_nudge and admin_views
 2. In your-site/admin/structure/views/view/admin_views_user/edit:

  * Add field: "Two-Factor Authentication: Two-Factor Security"
  * Add filter: "Two-Factor Authentication: Two-Factor Security"

This will create a field on your users table that displays an icon that indicates that user's TFA status. A lock icon indicates that TFA is enabled, a warning icon indicates that TFA is not enabled.

### Configuration

To configure list of users in [Administration Views] (https://www.drupal.org/project/admin_views) go to your-site/admin/structure/views/view/admin_views_user/edit.

 * Set up email notifications
  * Go to Two-factor Authentication Settings in Configuration 
  * Edit the subject and body of the notifications
  * Click "Enable email notifications"

### Project Information

Maintenance status: Actively maintained
Development status: Under active development
