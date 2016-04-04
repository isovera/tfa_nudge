# Two-Factor Authentication Nudge

### Overview

A strict policy of requiring two-factor authentication can sometimes be onerous for users. The purpose of this module is to help site administrators give users a gentle, but insistent [nudge] (https://en.wikipedia.org/wiki/Nudge_(book)) to set up two-factor authentication.

It makes two fields available to the [Administration Views] (https://www.drupal.org/project/admin_views) module: <i>Two-factor Security Status</i> and <i>Two-factor Saved Date</i>. It also provides a filter that can be exposed to selectively display a list of users based on their TFA status.

### Requirements

* [Two-factor Authentication (TFA)] (https://www.drupal.org/project/tfa)
* [TFA Basic plugins] (https://www.drupal.org/project/tfa_basic)
* [Administration Views] (https://www.drupal.org/project/admin_views)

### Usage

- Create an extra field on you-site/admin/people that displays a boolean value representing which users have TFA

- Filter by that value

### Installation

 1. download and enable tfa_nudge and admin_views
 2. In your-site/admin/structure/views/view/admin_views_user/edit:

  * Add field: "Two-Factor Authentication: Two-Factor Security"
  * Add filter: "Two-Factor Authentication: Two-Factor Security"

This will create a field on your users table that displays an icon that indicates that user's TFA status. A lock icon indicates that TFA is enabled, a warning icon indicates that TFA is not enabled.

### Configuration

You can change the configuration in your-site/admin/structure/views/view/admin_views_user/edit to show an icon for TFA users only, non-TFA users only, display 'yes' or 'no', checks or x's, '1' or '0', etc. instead of icons.
